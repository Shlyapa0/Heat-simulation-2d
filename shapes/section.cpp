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

// Функция для нахождения точки пересечения двух отрезков
// Возвращает std::optional<Point>, который содержит точку пересечения, если она есть,
// или std::nullopt, если отрезки не пересекаются или коллинеарны и не имеют общей точки.
std::optional<point> findIntersection(point p1, point q1, point p2, point q2) {
    // 1. Определяем ориентацию четырех троек точек:
    // (p1, q1, p2), (p1, q1, q2), (p2, q2, p1), (p2, q2, q1)

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

    // Особые случаи: одна из ориентаций равна 0
    // Это значит, что точки коллинеарны и точка лежит на отрезке

    // p2 лежит на отрезке [p1, q1]
    if (o1 == 0 && onSegment(p1, q1, p2)) return p2;

    // q2 лежит на отрезке [p1, q1]
    if (o2 == 0 && onSegment(p1, q1, q2)) return q2;

    // p1 лежит на отрезке [p2, q2]
    if (o3 == 0 && onSegment(p2, q2, p1)) return p1;

    // q1 лежит на отрезке [p2, q2]
    if (o4 == 0 && onSegment(p2, q2, q1)) return q1;

    return std::nullopt; // Отрезки не пересекаются
}

std::optional<point> section::intersect(section* a) {
    return findIntersection(this->p1, this->p2, a->p1, a->p2);
}