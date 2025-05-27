#include <pattern.h>
#include <iostream>

double D1u(double u1, double u2, double dh)
{
    return (u1-u2)/dh;
}

double D2u(double u_left, double u_center, double u_right, double dx_left, double dx_right) {
    double D1u_right = D1u(u_right, u_center, dx_right);
    double D1u_left = D1u(u_left, u_center, dx_left);
    return (D1u_right-D1u_left)/(dx_right+dx_left);
}

double calcLaplasian(double u_left, double u_right, double u_top, double u_bot, double dx_left, double dx_right, double u_center, double dy_bot, double dy_top) {
    return D2u(u_left, u_center, u_right, dx_left, dx_right)+D2u(u_bot, u_center, u_top, dy_bot, dy_top);
}

double calcPattern(double Ubot, double Utop, double Uleft, double Uright,
                   double dyBot, double dyTop, double dxLeft, double dxRight, double f) {

    //dxLeft=10000;
    //dxRight=10000;
    //dyBot=10000;
    //dyTop=10000;

    double numerator = f - (2. * Ubot) / (dyBot * (dyBot + dyTop)) -
                     (2. * Uleft) / (dxLeft * (dxLeft + dxRight)) -
                     (2. * Uright) / (dxRight * (dxLeft + dxRight)) -
                     (2. * Utop) / (dyTop * (dyBot + dyTop));

    double denominator = (-2. / (dxLeft * (dxLeft + dxRight))) -
                       2. / (dxRight * (dxLeft + dxRight)) -
                       2. / (dyBot * (dyBot + dyTop)) -
                       2. / (dyTop * (dyBot + dyTop));
    
    //std::cout << "Uright" << Uright << ", Uleft: " << Uleft << ", Utop: " << Utop << ", Ubot: " << Ubot << std::endl;

    if (std::abs(denominator) < 1e-10) {
        std::cout << "Warning: Denominator is too small, returning 0." << std::endl;
        std::cout << "Ubot: " << Ubot << ", Utop: " << Utop << ", Uleft: " << Uleft << ", Uright: " << Uright << std::endl;
        std::cout << "dyBot: " << dyBot << ", dyTop: " << dyTop << ", dxLeft: " << dxLeft << ", dxRight: " << dxRight << std::endl;
        std::cout << "f: " << f << std::endl;
        //std::abort();
    }
    if (dyBot < 1e-10 || dyTop < 1e-10 || dxLeft < 1e-10 || dxRight < 1e-10) {
        std::cout << "Warning: One of the dimensions is too small, returning 0." << std::endl;
        std::cout << "Ubot: " << Ubot << ", Utop: " << Utop << ", Uleft: " << Uleft << ", Uright: " << Uright << std::endl;
        std::cout << "dyBot: " << dyBot << ", dyTop: " << dyTop << ", dxLeft: " << dxLeft << ", dxRight: " << dxRight << std::endl;
        //std::abort();
    }

    return numerator / denominator;
}
