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
    private:
        const Point& start_point;
        const Point& end_point;
};

#endif