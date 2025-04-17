#ifndef SECTION_H
#define SECTION_H

#include <shapes/point.h>
#include <optional>
#include <shapes/arc.h>

struct section : public Shape {
    point p1;
    point p2;
    section(point p1, point p2);
    std::optional<point> intersect(section* s);
    std::optional<point> intersect(const arc& arc) const;
    std::optional<point> intersect(const section& sec) const;
};

#endif