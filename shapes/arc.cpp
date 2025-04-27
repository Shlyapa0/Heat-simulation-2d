#include "shapes/arc.h"
#include <cmath>

Arc::Arc(const Point& p0, double rad, double ang_start, double ang_end) {
    center_point = p0;
    radius = rad;
    start_angle = ang_start;
    end_angle = ang_end;
}

Point Arc::getCenterPoint() const {
    return center_point;
}

double Arc::getRadius() const {
    return radius;
}

double Arc::normalizeAngle(double angle) const {
    while (angle < 0) {
        angle += 2 * M_PI;
    }
    while (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}

bool Arc::isPointOnArc(const Point& Point) const {
    // Calculate the angle of the Point relative to the arc's center
    double angle = atan2(Point.getY() - center_point.getY(), Point.getX() - center_point.getX());
    // Normalize the angle to be between 0 and 2*PI

    angle = normalizeAngle(angle);

    double start = start_angle;
    double end = end_angle;

    while (start < 0) start += 2 * M_PI;
    while (start >= 2 * M_PI) start -= 2 * M_PI;
    while (end < 0) end += 2 * M_PI;
    while (end >= 2 * M_PI) end -= 2 * M_PI;

    // Check if the angle is within the arc's range, handling wrap-around cases.
    if (start <= end) {
        return (angle >= start && angle <= end);
    } else {
        return (angle >= start || angle <= end);
    }
}