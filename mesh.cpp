#include <mesh.h>
#include <shapes/section.h>
#include <iostream>
#include <fstream>
#include <cmath>

#define EPS 1e-7

Mesh::Mesh(Region reg, double max_cell_size, double max_reg_size, double cell_sz, Point& initial_p) {
    initial_point = initial_p;
    std::ofstream fout;
    fout.open("mesh.txt");
    cell_size = cell_sz;
    std::cout << "Cell size: " << cell_sz << std::endl;
    Point p1 = Point(max_reg_size, initial_point.getY());
    Point p2 = Point(-max_reg_size, initial_point.getY());
    Section* ray1 = new Section(initial_point, p1);
    Section* ray2 = new Section(initial_point, p2);
    std::vector<Point*> initialPoints;
    initialPoints.push_back(new Point(initial_point.getX(), initial_point.getY()));
    std::cout << "Regsize: " << reg.getSize() << std::endl;
    for (int i=0; i<reg.getSize(); i++) {
        std::optional<const Shape*> ptr1 = ray1->intersect(reg.getShape(i));
        getPointsX(initialPoints, ptr1);
        std::optional<const Shape*> ptr2 = ray2->intersect(reg.getShape(i));
        getPointsX(initialPoints, ptr2);
    }
    std::cout << "initial points: " << std::endl;
    for (auto point : initialPoints) {
        std::cout << point->getX() << ' ' << point->getY() << std::endl;
    }
    //std::vector<Point*> allPoints=initialPoints;
    allPoints=initialPoints;
    for (auto point : initialPoints) {
        Point p1 = Point(point->getX(), max_reg_size);
        Point p2 = Point(point->getX(), -max_reg_size);
        Section* ray1 = new Section(*point, p1);
        Section* ray2 = new Section(*point, p2);
        for (int i=0; i<reg.getSize(); i++) {
            std::optional<const Shape*> ptr1 = ray1->intersect(reg.getShape(i));
            getPointsY(allPoints, point, ptr1);
            std::optional<const Shape*> ptr2 = ray2->intersect(reg.getShape(i));
            getPointsY(allPoints, point, ptr2);
        }
    }
    for (auto point : allPoints) {
        fout << point->getX() << ' ' << point->getY() << ' ' << point->getBorder() << std::endl;
    }
    fout.close();
}

int Mesh::getSize() {
    return cell_size;
}

std::vector<Point*> Mesh::getPoints() {
    return allPoints;
}

void Mesh::getPointsX(std::vector<Point*>& initialPoints, std::optional<const Shape*> ptr1) {
    if (ptr1!=std::nullopt) {
        double x1 = static_cast<const Point*>(ptr1.value())->getX();
        double y0 = initial_point.getY();
        double x0 = initial_point.getX();
        Point* newPoint = new Point(x1, y0);
        newPoint->setBorder(1);
        initialPoints.push_back(newPoint);
        for (; std::abs(x1 - x0) > 2*cell_size;) {
            double step = (x1 > x0) ? -cell_size : cell_size;
            x1 += step;
            initialPoints.push_back(new Point(x1, y0));
        }
    }
}

void Mesh::getPointsY(std::vector<Point*>& allPoints, Point* initial_point, std::optional<const Shape*> ptr1) {
    if ((ptr1!=std::nullopt)) {
        double y1 = static_cast<const Point*>(ptr1.value())->getY();
        double y0 = initial_point->getY();
        double x0 = initial_point->getX();
        Point* newPoint = new Point(x0, y1);
        newPoint->setBorder(1);
        allPoints.push_back(newPoint);
        for (; std::abs(y1 - y0) > cell_size;) {
            double step = (y1 > y0) ? -cell_size : cell_size;
            y1 += step;
            Point* newPoint = new Point(x0, y1);
            newPoint->setBorder(initial_point->getBorder());
            allPoints.push_back(newPoint);
        }
    }
}