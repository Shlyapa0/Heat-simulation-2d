#include "shapes/point.h"

Point::Point() {
    x=0.;
    y=0.;
}

Point::Point(const double x_val, const double y_val) {
    x=x_val;
    y=y_val;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}