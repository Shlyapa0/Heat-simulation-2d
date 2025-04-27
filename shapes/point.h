#ifndef POINT_H
#define POINT_H

#include <shapes/shape.h>

struct Point : public Shape {
    public:
        Point();
        Point(double x_val, double y_val);
        double getX() const;
        double getY() const;
        std::optional<const Shape*> intersect(const Shape* other) const override {return std::nullopt;};
        ~Point() override {};
    private:
        double x;
        double y;
};

#endif