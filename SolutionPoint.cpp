#include <SolutionPoint.h>

SolutionPoint::SolutionPoint() : x(0), y(0), value(0), num_border(0) {}

SolutionPoint::SolutionPoint(const double x_val, const double y_val) : x(x_val), y(y_val), value(0), num_border(0) {}

SolutionPoint::SolutionPoint(const double x_val, const double y_val, const double value_val) : x(x_val), y(y_val), value(value_val), num_border(0) {}

SolutionPoint& SolutionPoint::operator=(const SolutionPoint& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        value = other.value;
        num_border = other.num_border;
    }
    return *this;
}

double SolutionPoint::getX() const {
    return x;
}

double SolutionPoint::getY() const {
    return y;
}

double SolutionPoint::getValue() const {
    return value;
}

void SolutionPoint::setValue(double value_val) {
    value = value_val;
}

