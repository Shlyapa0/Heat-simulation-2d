#ifndef ARC_H
#define ARC_H

#include <shapes/point.h>

struct arc : public Shape {
    point center_p;
    double radius;
    double start_angle;
    double end_angle;
    arc(point center_p, double radius, double start_angle, double end_angle);
};

#endif