#ifndef SHAPE_H
#define SHAPE_H

#include <optional>
#include <memory>

class Shape {
    using IntersectResult = std::optional<Shape*>;
    public:
        Shape() {};
        virtual std::optional<const Shape*> intersect(const Shape* other) const = 0;
        virtual ~Shape() {};
};

#endif