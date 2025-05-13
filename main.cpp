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
    std::vector<Shape*> shapes = std::vector<Shape*> {
        // new Section(p1, p2),
        // new Section(p2, p3),
        // new Arc(p4, rad/4, M_PI, 3*M_PI_2),
        // new Section(p5, p6),
        // new Section(p6,p1)
        new Section(p1, p2),
        new Section(p2, p3),
        new Section(p3, Point(0.25,1.45)),
        new Section(Point(0.25,1.45), Point(0.50,1.25)),
        new Section(Point(0.50,1.25), p5),
        //new Section(p3, p5),
        new Section(p5, p6),
        new Section(p6,p1)
    };
    Region region(shapes);
    Section* a =  new Section(Point(0,0), Point(4,4));
    Section* b = new Section(Point(4,0), Point(0,4));
    Arc* aarc = new Arc(Point(4,4), 2., M_PI, 3*M_PI_2);
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
    Mesh mesh(region, 5., 0.1, init_point);
    Solver solver(mesh, nullptr, nullptr);
    solver.GetInitialPoints();
    solver.PrintToFile("output_init.txt");
    solver.Run();
    // for (int i=0; i<2; ++i) {
    //     // solver.PrintToFile("output.txt");
    //     solver.Step();
    // }
    solver.PrintToFile("output.txt");
    return 0;
}
