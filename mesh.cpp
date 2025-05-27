#include <mesh.h>
#include <shapes/section.h>
#include <iostream>
#include <fstream>
#include <cmath>

//#define EPS 1e-7

const double EPS = std::numeric_limits<double>::epsilon() * 1e8;

Mesh::Mesh(Region reg, double max_reg_size, double cell_sz, Point& initial_p) {
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
    neighborInfo.resize(allPoints.size());
    for (int i=0; i<allPoints.size(); i++) {
        if (allPoints[i]->getBorder()==0)
        addBorder(i, reg);
    }
    findNeighbors();
    std::size_t index = 0;
    for (auto point : allPoints) {
        //fout << index << ": " << point->getX() << ' ' << point->getY() << ' ' << point->getBorder() << std::endl;
        fout << point->getX() << ' ' << point->getY() << ' ' << point->getBorder() << std::endl;
        index++;
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
        for (; std::abs(x1 - x0) > cell_size;) {
            double step = (x1 > x0) ? -cell_size : cell_size;
            x1 += step;
            if (std::abs(x1 - x0) < EPS) {
                continue;
            }
            initialPoints.push_back(new Point(x1, y0));
            //initialPoints.back()->setBorder(1);
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
            y0 -= step;
            if (std::abs(y1 - y0) < EPS) {
                continue;
            }
            Point* newPoint = new Point(x0, y0);
            newPoint->setBorder(initial_point->getBorder());
            allPoints.push_back(newPoint);
        }
    }
}

void Mesh::findNeighbors(int index) {
    double x = allPoints[index]->getX();
    double y = allPoints[index]->getY();

    for (int j = 0; j < allPoints.size(); ++j) {
        if (index == j) continue;

        double dx = allPoints[j]->getX() - x;
        double dy = allPoints[j]->getY() - y;

        // Проверяем, находятся ли точки достаточно близко друг к другу
        if (std::abs(dx) < cell_size+EPS && std::abs(dy) < cell_size+EPS) {
            //if (std::abs(dx) < EPS) {
            if (std::abs(dx) < cell_size+EPS && std::abs(dx) > EPS) {
                // Проверяем, является ли точка j соседом точки i (вверх, вниз).
                if (dy>0) {
                    if (neighborInfo[index].upIndex == -1 || dy < std::abs(allPoints[neighborInfo[index].upIndex]->getY() - y)) {
                        neighborInfo[index].upIndex = j;
                    }
                } else if (dy<0) {
                    if (neighborInfo[index].downIndex == -1 || dy > std::abs(allPoints[neighborInfo[index].downIndex]->getY() - y)) {
                        neighborInfo[index].downIndex = j;
                    }
                }
            }
            //if (std::abs(dy) < EPS){
            if (std::abs(dy) < cell_size+EPS && std::abs(dy) > EPS) {
                // Проверяем, является ли точка j соседом точки i (влево, вправо).
                if (dx<0) {
                    if (neighborInfo[index].leftIndex == -1 || dx > std::abs(allPoints[neighborInfo[index].leftIndex]->getX() - x)) {
                        neighborInfo[index].leftIndex = j;
                    }
                } else if (dx>0) {
                    if (neighborInfo[index].rightIndex == -1 || dx < std::abs(allPoints[neighborInfo[index].rightIndex]->getX() - x)) {
                        neighborInfo[index].rightIndex = j;
                    }
                }

            }
        }
    }
}

void Mesh::addBorder(int index, Region reg) {
    if (neighborInfo[index].upIndex == -1) {
        Section* ray = new Section(*allPoints[index], Point(allPoints[index]->getX(), allPoints[index]->getY() + cell_size + EPS));
        for (int i=0; i<reg.getSize(); i++) {
            std::optional<const Shape*> ptr1 = ray->intersect(reg.getShape(i));
            if (ptr1 != std::nullopt) {
                double y1 = static_cast<const Point*>(ptr1.value())->getY();
                double x0 = allPoints[index]->getX();
                Point* newPoint = new Point(x0, y1);
                newPoint->setBorder(1);
                allPoints.push_back(newPoint);
            }
        }
    }
    if (neighborInfo[index].downIndex == -1) {
        Section* ray = new Section(*allPoints[index], Point(allPoints[index]->getX(), allPoints[index]->getY() - cell_size - EPS));
        for (int i=0; i<reg.getSize(); i++) {
            std::optional<const Shape*> ptr1 = ray->intersect(reg.getShape(i));
            if (ptr1 != std::nullopt) {
                double y1 = static_cast<const Point*>(ptr1.value())->getY();
                double x0 = allPoints[index]->getX();
                Point* newPoint = new Point(x0, y1);
                newPoint->setBorder(1);
                allPoints.push_back(newPoint);
            }
        }
    }
    if (neighborInfo[index].leftIndex == -1) {
        Section* ray = new Section(*allPoints[index], Point(allPoints[index]->getX() - cell_size - EPS, allPoints[index]->getY()));
        for (int i=0; i<reg.getSize(); i++) {
            std::optional<const Shape*> ptr1 = ray->intersect(reg.getShape(i));
            if (ptr1 != std::nullopt) {
                double x1 = static_cast<const Point*>(ptr1.value())->getX();
                double y0 = allPoints[index]->getY();
                Point* newPoint = new Point(x1, y0);
                newPoint->setBorder(1);
                allPoints.push_back(newPoint);
            }
        }
    }
    if (neighborInfo[index].rightIndex == -1) {
        Section* ray = new Section(*allPoints[index], Point(allPoints[index]->getX() + cell_size + EPS, allPoints[index]->getY()));
        for (int i=0; i<reg.getSize(); i++) {
            std::optional<const Shape*> ptr1 = ray->intersect(reg.getShape(i));
            if (ptr1 != std::nullopt) {
                double x1 = static_cast<const Point*>(ptr1.value())->getX();
                double y0 = allPoints[index]->getY();
                Point* newPoint = new Point(x1, y0);
                newPoint->setBorder(1);
                allPoints.push_back(newPoint);
            }
        }
    }
}

void Mesh::findNeighbors() {
    neighborInfo.resize(allPoints.size());
    for (int i = 0; i < allPoints.size(); ++i) {
        findNeighbors(i);
    }
}

std::vector<NeighborInfo> Mesh::getNeighborInfo() {
    findNeighbors();
    return neighborInfo;
}