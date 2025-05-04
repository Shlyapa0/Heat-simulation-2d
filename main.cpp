#include "mesh.h"

#include <cmath>
#include <vector>
#include <iostream>

#include "region.h"
#include "shapes/point.h"
#include "shapes/shape.h"
#include "shapes/section.h"
#include "shapes/arc.h"
#include "Solver.h"

double D1u(double u1, double u2, double dh)
{
    return (u1-u2)/dh;
}

double D2u(double u_left, double u_center, double u_right, double dx_left, double dx_right) {
    double D1u_right = D1u(u_right, u_center, dx_right);
    double D1u_left = D1u(u_left, u_center, dx_left);
    return (D1u_right-D1u_left)/(dx_right+dx_left);
}

double calcPattern(double u_left, double u_right, double u_top, double u_bot, double dx_left, double dx_right, double u_center, double dy_bot, double dy_top) {
    return D2u(u_left, u_center, u_right, dx_left, dx_right)+D2u(u_bot, u_center, u_top, dy_bot, dy_top);
}

double* doStep(double* numbers) {
    double* numbers1;
    return numbers1;
}

int main() {
    Point p1 = Point(-1,0);
    Point p2 = Point(-1,2);
    Point p3 = Point(0,2);
    Point p4 = Point(1,2);
    double rad = 1;
    Point p5 = Point(1,1);
    Point p6 = Point(1,0);
    Point p33 = Point(1,2);
    std::vector<Shape*> shapes = std::vector<Shape*> {
        // new Section(p1, p2),
        // new Section(p2, p3),
        // new Arc(p4, rad, M_PI, 3*M_PI_2),
        // new Section(p5, p6),
        // new Section(p6,p1)
        new Section(p1, p2),
        new Section(p2, p3),
        new Section(p3, p33),
        new Section(p33, p5),
        new Section(p5, p6),
        new Section(p6,p1)
    };
    Region region(shapes);
    Section* a =  new Section(Point(0,0), Point(4,4));
    Section* b = new Section(Point(4,0), Point(0,4));
    Arc* aarc = new Arc(Point(4,4), 1., M_PI, 3/2*M_PI);
    std::optional<const Shape*> intersection = a->intersect(aarc);
    if (intersection.has_value()) {
        const Shape* shapePtr = intersection.value();
        if (const Point* pointPtr = dynamic_cast<const Point*>(shapePtr)) {
            std::cout << "x: " << pointPtr->getX() << ", y: " << pointPtr->getY() << std::endl;
        } else {
            std::cout << "Intersection is not a Point!" << std::endl;
        }
        } else {
        std::cout << "No intersection." << std::endl;
    }
    Point init_point = Point(0.0,0.5);
    Mesh mesh(region, 0.1, 5., 0.1, init_point);
    Solver solver(mesh, nullptr, nullptr);
    solver.GetInitialPoints();
    solver.PrintToFile("output.txt");
    return 0;
}
