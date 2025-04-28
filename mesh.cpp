#include <mesh.h>
#include <shapes/section.h>
#include <iostream>
#include <fstream>

Mesh::Mesh(Region reg, double max_cell_size, double max_reg_size, Point& initial_point) {
    std::ofstream fout;
    fout.open("mesh.txt");
    double cell_size = 0.1;
    size = 0.1;
    Point p1 = Point(max_reg_size, initial_point.getY());
    Point p2 = Point(-max_reg_size, initial_point.getY());
    Section* ray1 = new Section(initial_point, p1);
    Section* ray2 = new Section(initial_point, p2);
    std::vector<Point*> initialPoints;
    std::cout << "Regsize: " << reg.getSize() << std::endl;
    for (int i=0; i<reg.getSize(); i++) {
        std::optional<const Shape*> ptr1 = ray1->intersect(reg.getShape(i));
        std::cout << "Checked shape" << i << ' ' << (ptr1==std::nullopt) << std::endl;
        if (ptr1!=std::nullopt) {
            double x1 = dynamic_cast<const Point*>(ptr1.value())->getX();
            double y0 = initial_point.getY();
            double x0 = initial_point.getX();
            std::cout << x0 << ' ' << y0 << ' ' << x1 << std::endl;
            for (;x1>x0;x1-=cell_size) {
                initialPoints.push_back(new Point(x1, y0));
                fout << x1 << ' ' << y0 << std::endl;
            }
        }
        std::optional<const Shape*> ptr2 = ray2->intersect(reg.getShape(i));
        if (ptr2!=std::nullopt) {
            double x1 = dynamic_cast<const Point*>(ptr2.value())->getX();
            double y0 = initial_point.getY();
            double x0 = initial_point.getX();
            std::cout << x0 << ' ' << y0 << ' ' << x1 << std::endl;
            for (;x1<x0;x1+=cell_size) {
                initialPoints.push_back(new Point(x1, y0));
                fout << x1 << ' ' << y0 << std::endl;
            }
        }
    }
    for (auto point : initialPoints) {
        std::cout << point->getX() << ' ' << point->getY() << std::endl;
    }
    fout.close();
}

int Mesh::getSize() {
    return size;
}

Point* Mesh::getDataPointer() {
    return points;
}