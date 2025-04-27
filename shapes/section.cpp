#include <shapes/section.h>
#include <algorithm>
#include <optional>
#include <cmath>

Section::Section(const Point& start, const Point& end) : start_point(start), end_point(end) {}

double crossProduct(const Point& a, const Point& b, const Point& c) {
    return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
}

bool onSegment(const Point& a, const Point& b, const Point& c) {
    if (c.getX() <= std::max(a.getX(), b.getX()) && c.getX() >= std::min(a.getX(), b.getX()) &&
        c.getY() <= std::max(a.getY(), b.getY()) && c.getY() >= std::min(a.getY(), b.getY()))
        return true;
    return false;
}

std::optional<const Shape*> Section::intersect(const Shape* other) const {
    // Check if the other shape is an Arc
    if (const Arc* arc = dynamic_cast<const Arc*>(other)) {

        // Line equation: y = mx + b
        double m = (end_point.getY() - start_point.getY()) / (end_point.getX() - start_point.getX());
        double b = start_point.getY() - m * start_point.getX();

        // Circle equation: (x - center_x)^2 + (y - center_y)^2 = radius^2
        // Substitute y = mx + b into the circle equation and solve for x
        double A = 1 + m * m;
        double B = 2 * (m * (b - arc->getCenterPoint().getX()) - arc->getCenterPoint().getX());
        double C = pow(arc->getCenterPoint().getX(), 2) + pow(b - arc->getCenterPoint().getX(), 2) - pow(arc->getRadius(), 2);

        double discriminant = B * B - 4 * A * C;

        if (discriminant >= 0) {
            double x1 = (-B + sqrt(discriminant)) / (2 * A);
            double x2 = (-B - sqrt(discriminant)) / (2 * A);

            Point* p1 = new Point(x1, m * x1 + b);
            Point* p2 = new Point(x2, m * x2 + b);

            // Check if the intersection points are within the line segment AND on the arc

            if (onSegment(start_point, end_point, *p1) && arc->isPointOnArc(*p1)) return p1;
            if (onSegment(start_point, end_point, *p2) && arc->isPointOnArc(*p2)) return p2;
        }
    }
    //Check if the other shape is a section
    if (const Section* section = dynamic_cast<const Section*>(other)) {
        Point p1 = this->start_point;
        Point q1 = this->end_point;
        Point p2 = section->start_point;
        Point q2 = section->end_point;
        double o1 = crossProduct(p1, q1, p2);
        double o2 = crossProduct(p1, q1, q2);
        double o3 = crossProduct(p2, q2, p1);
        double o4 = crossProduct(p2, q2, q1);
         // Общий случай: отрезки пересекаются
        if (o1 * o2 < 0 && o3 * o4 < 0) {
            // Вычисляем точку пересечения
            double det = (p1.getX() - q1.getX()) * (p2.getY() - q2.getY()) - (p1.getY() - q1.getY()) * (p2.getX() - q2.getX());
            if (det == 0) {
                return std::nullopt; // Отрезки параллельны
            }

            double t = ((p1.getX() - p2.getX()) * (p2.getY() - q2.getY()) - (p1.getY() - p2.getY()) * (p2.getX() - q2.getX())) / (double)det;
            double u = -((p1.getX() - q1.getX()) * (p1.getY() - p2.getY()) - (p1.getY() - q1.getY()) * (p1.getX() - p2.getX())) / (double)det;

            double x_int = p1.getX() + t * (q1.getX() - p1.getX());
            double y_int = p1.getY() + t * (q1.getY() - p1.getY());
            Point* intersection = new Point(x_int, y_int);
            return intersection;
        }
        if (o1 == 0 && onSegment(p1, q1, p2)) {
            Point *intersectionPoint = new Point(p2.getX(), p2.getY());
            return intersectionPoint;
        }
        if (o2 == 0 && onSegment(p1, q1, q2)) {
            Point *intersectionPoint = new Point(q2.getX(), q2.getY());
            return intersectionPoint;
        }
        if (o3 == 0 && onSegment(p2, q2, p1)) {
            Point *intersectionPoint = new Point(p1.getX(), p1.getY());
            return intersectionPoint;
        }
        if (o4 == 0 && onSegment(p2, q2, q1)) {
            Point *intersectionPoint = new Point(q1.getX(), q1.getY());
            return intersectionPoint;
        }
        return std::nullopt; // Отрезки не пересекаются
    }
    // Check if the other shape is a point
    if (const Point* point = dynamic_cast<const Point*>(other)) {
        if (onSegment(start_point, end_point, *point)){
            return point;
        }
    }
    //If the shape isn't an Arc, then there is no intersection by default
    return std::nullopt;
}