#ifndef POINT_H
#define POINT_H

#include <shapes/shape.h>

struct point : public Shape {
    double x;
    double y;
    point();
    point(double x_val, double y_val);
};

#endif