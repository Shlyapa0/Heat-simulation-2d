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

        double arcCenterPointX = arc->getCenterPoint().getX();
        double arcCenterPointY = arc->getCenterPoint().getX();

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
    // Check if the other shape is a point
    if (const Point* point = dynamic_cast<const Point*>(other)) {
        //Check if point lies on section

        if (onSegment(start_point, end_point, *point)){
            return point;
        }
    }

    //If the shape isn't an Arc, then there is no intersection by default
    return std::nullopt;
}

// std::optional<Point> findIntersection(Point p1, Point q1, Point p2, Point q2) {

//     double o1 = crossProduct(p1, q1, p2);
//     double o2 = crossProduct(p1, q1, q2);
//     double o3 = crossProduct(p2, q2, p1);
//     double o4 = crossProduct(p2, q2, q1);

//     // Общий случай: отрезки пересекаются
//     if (o1 * o2 < 0 && o3 * o4 < 0) {
//         // Вычисляем точку пересечения
//         double det = (p1.x - q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x - q2.x);
//         if (det == 0) {
//             return std::nullopt; // Отрезки параллельны
//         }

//         double t = ((p1.x - p2.x) * (p2.y - q2.y) - (p1.y - p2.y) * (p2.x - q2.x)) / (double)det;
//         double u = -((p1.x - q1.x) * (p1.y - p2.y) - (p1.y - q1.y) * (p1.x - p2.x)) / (double)det;

//         Point intersection;
//         intersection.x = p1.x + t * (q1.x - p1.x);
//         intersection.y = p1.y + t * (q1.y - p1.y);
//         return intersection;
//     }
//     if (o1 == 0 && onSegment(p1, q1, p2)) return p2;
//     if (o2 == 0 && onSegment(p1, q1, q2)) return q2;
//     if (o3 == 0 && onSegment(p2, q2, p1)) return p1;
//     if (o4 == 0 && onSegment(p2, q2, q1)) return q1;

//     return std::nullopt; // Отрезки не пересекаются
// }

// std::optional<Point> section::intersect(const arc& arc) const {
//     // y = mx + b
//     double m = (p2.y - p1.y) / (p2.x - p1.x);
//     double b = p1.y - m * p1.x;

//     // (x - center_x)^2 + (y - center_y)^2 = radius^2
//     double A = 1 + m * m;
//     double B = 2 * (m * (b - arc.center_p.y) - arc.center_p.x);
//     double C = pow(arc.center_p.x, 2) + pow(b - arc.center_p.y, 2) - pow(arc.radius, 2);

//     double discriminant = B * B - 4 * A * C;

//     if (discriminant >= 0) {
//         double x1 = (-B + sqrt(discriminant)) / (2 * A);
//         double x2 = (-B - sqrt(discriminant)) / (2 * A);

//         Point p11 = {x1, m * x1 + b};
//         Point p22 = {x2, m * x2 + b};

//         // Check if the intersection Points are within the line segment
//         if (onSegment(p1, p2, p11) && arc.isPointOnArc(p11)) return p11;
//         if (onSegment(p1, p2, p22) && arc.isPointOnArc(p22)) return p22;
//     }

//     return std::nullopt;
// }

// std::optional<Point> section::intersect(section* a) {
//     return findIntersection(this->p1, this->p2, a->p1, a->p2);
// }

// std::optional<Point> section::intersect(const section& sec) const {
//     return findIntersection(p1, p2, sec.p1, sec.p2);
// }