#ifndef PATTERN_H
#define PATTERN_H
#include <pattern.h>

double D1u(double u1, double u2, double dh)
{
    return (u1-u2)/dh;
}

double D2u(double u_left, double u_center, double u_right, double dx_left, double dx_right) {
    double D1u_right = D1u(u_right, u_center, dx_right);
    double D1u_left = D1u(u_left, u_center, dx_left);
    return (D1u_right-D1u_left)/(dx_right+dx_left);
}

// double calcPattern(double u_left, double u_right, double u_top, double u_bot, double dx_left, double dx_right, double u_center, double dy_bot, double dy_top) {
//     return D2u(u_left, u_center, u_right, dx_left, dx_right)+D2u(u_bot, u_center, u_top, dy_bot, dy_top);
// }

double calcPattern(double u_left, double u_right, double u_top, double u_bot, 
                    double dx_left, double dx_right, double dy_bot, double dy_top) {
    return (u_top/dy_top*(dx_right+dx_left) - u_bot/dy_bot*(dx_right+dx_left) + 
            u_right/dx_right*(dy_top+dy_bot) - u_left/dx_left*(dy_top+dy_bot))/(1 / dy_bot*(dx_right+dx_left) + 
            1 / dy_top*(dx_right+dx_left) + 1 / dx_right*(dy_top+dy_bot) + 1 / dx_left*(dy_top+dy_bot));
}

#endif // PATTERN_H