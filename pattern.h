#ifndef PATTERN_H
#define PATTERN_H

double D1u(double u1, double u2, double dh);
double D2u(double u_left, double u_center, double u_right, double dx_left, double dx_right);
double calcPattern(double Ubot, double Utop, double Uleft, double Uright,
                   double dyBot, double dyTop, double dxLeft, double dxRight, double source);

#endif // PATTERN_H