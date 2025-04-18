#include "mesh.h"
#include <cmath>
#include "iostream"
#include "region.h"
#include "shapes/point.h"
#include "shapes/shape.h"
#include "shapes/section.h"
#include "shapes/arc.h"

double D1u(double u1, double u2, double dh)
{
    return (u1-u2)/dh;
}

double D2u(double u_left, double u_center, double u_right, double dx_left, double dx_right) {
    double D1u_right = D1u(u_right, u_center, dx_right);
    double D1u_left = D1u(u_left, u_center, dx_left);
    return (D1u_right-D1u_left)/(dx_right+dx_left);
}

double calcPattern(double u_left, double u_right, double u_top, double u_bot, double dx_left, double dx_right, double u_center, double dy_bot, double dy_top) {
    return D2u(u_left, u_center, u_right, dx_left, dx_right)+D2u(u_bot, u_center, u_top, dy_bot, dy_top);
}

double* doStep(double* numbers) {
    double* numbers1;
    return numbers1;
}

int main() {
    int N=100;
    int M=100;
    section a =  section(point(0,0), point(4,0));
    section b = section(point(0,0), point(2,0));
    arc aarc = arc(point(2,0), 1, M_PI/2, 3/2*M_PI);
    std::optional p = a.intersect(b);
    std::cout << p->x << " " << p->y << std::endl;
    p = a.intersect(aarc);
    std::cout << p->x << " " << p->y << std::endl;
    return 0;
}
