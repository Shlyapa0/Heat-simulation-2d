#ifndef SECTION_H
#define SECTION_H

#include <shapes/point.h>
#include <optional>
#include <shapes/arc.h>

struct Section : public Shape {
    public:
        Section(const Point& p1, const Point& p2);
        std::optional<const Shape*> intersect(const Shape* other) const override;
        ~Section() override {};
        // std::optional<Point> intersect(section* s);
        // std::optional<Point> intersect(const arc& arc) const;
        // std::optional<Point> intersect(const section& sec) const;
    private:
        const Point& start_point;
        const Point& end_point;
};

#endif