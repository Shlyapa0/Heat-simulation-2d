#include <shapes/section.h>
#include <algorithm>
#include <optional>
#include <cmath>

section::section(point point1, point point2) {
    p1=point1;
    p2=point2;
}

double crossProduct(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool onSegment(point a, point b, point c) {
    if (c.x <= std::max(a.x, b.x) && c.x >= std::min(a.x, b.x) &&
        c.y <= std::max(a.y, b.y) && c.y >= std::min(a.y, b.y))
        return true;
    return false;
}

std::optional<point> findIntersection(point p1, point q1, point p2, point q2) {

    double o1 = crossProduct(p1, q1, p2);
    double o2 = crossProduct(p1, q1, q2);
    double o3 = crossProduct(p2, q2, p1);
    double o4 = crossProduct(p2, q2, q1);

    // Общий случай: отрезки пересекаются
    if (o1 * o2 < 0 && o3 * o4 < 0) {
        // Вычисляем точку пересечения
        double det = (p1.x - q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x - q2.x);
        if (det == 0) {
            return std::nullopt; // Отрезки параллельны
        }

        double t = ((p1.x - p2.x) * (p2.y - q2.y) - (p1.y - p2.y) * (p2.x - q2.x)) / (double)det;
        double u = -((p1.x - q1.x) * (p1.y - p2.y) - (p1.y - q1.y) * (p1.x - p2.x)) / (double)det;

        point intersection;
        intersection.x = p1.x + t * (q1.x - p1.x);
        intersection.y = p1.y + t * (q1.y - p1.y);
        return intersection;
    }
    if (o1 == 0 && onSegment(p1, q1, p2)) return p2;
    if (o2 == 0 && onSegment(p1, q1, q2)) return q2;
    if (o3 == 0 && onSegment(p2, q2, p1)) return p1;
    if (o4 == 0 && onSegment(p2, q2, q1)) return q1;

    return std::nullopt; // Отрезки не пересекаются
}

std::optional<point> section::intersect(const arc& arc) const {
    // y = mx + b
    double m = (p2.y - p1.y) / (p2.x - p1.x);
    double b = p1.y - m * p1.x;

    // (x - center_x)^2 + (y - center_y)^2 = radius^2
    double A = 1 + m * m;
    double B = 2 * (m * (b - arc.center_p.y) - arc.center_p.x);
    double C = pow(arc.center_p.x, 2) + pow(b - arc.center_p.y, 2) - pow(arc.radius, 2);

    double discriminant = B * B - 4 * A * C;

    if (discriminant >= 0) {
        double x1 = (-B + sqrt(discriminant)) / (2 * A);
        double x2 = (-B - sqrt(discriminant)) / (2 * A);

        point p11 = {x1, m * x1 + b};
        point p22 = {x2, m * x2 + b};

        // Check if the intersection points are within the line segment
        if (onSegment(p1, p2, p11) && arc.isPointOnArc(p11)) return p11;
        if (onSegment(p1, p2, p22) && arc.isPointOnArc(p22)) return p22;
    }

    return std::nullopt;
}

std::optional<point> section::intersect(section* a) {
    return findIntersection(this->p1, this->p2, a->p1, a->p2);
}

std::optional<point> section::intersect(const section& sec) const {
    return findIntersection(p1, p2, sec.p1, sec.p2);
}