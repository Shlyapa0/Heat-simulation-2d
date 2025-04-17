#ifndef SECTION_H
#define SECTION_H

#include <shapes/point.h>
#include <optional>

struct section : public Shape {
    point p1;
    point p2;
    section(point p1, point p2);
    std::optional<point> intersect(section* s);
};

#endif