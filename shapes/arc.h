#ifndef ARC_H
#define ARC_H

#include <shapes/point.h>

struct Arc : public Shape {
    public:
        Arc(const Point& center_p, double radius, double start_angle, double end_angle);
        double normalizeAngle(double angle) const;
        bool isPointOnArc(const Point& Point) const;
        Point getCenterPoint() const;
        double getRadius() const;
        std::optional<const Shape*> intersect(const Shape* other) const override {return std::nullopt;};
    private:
        Point center_point;
        double radius;
        double start_angle;
        double end_angle;
};

#endif