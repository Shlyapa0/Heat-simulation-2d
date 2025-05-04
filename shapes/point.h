#ifndef POINT_H
#define POINT_H

#include <shapes/shape.h>

struct Point : public Shape {
    public:
        Point();
        Point(const double x_val, const double y_val);
        Point(const Point& other) : x(other.x), y(other.y) {}
        Point& operator=(const Point& other);
        double getX() const;
        double getY() const;
        int getBorder() const;
        void setBorder(const int num_border);
        std::optional<const Shape*> intersect(const Shape* other) const override {return std::nullopt;};
        ~Point() override {};
    private:
        double x;
        double y;
        int num_border = 0; //0 - not a border
};

#endif