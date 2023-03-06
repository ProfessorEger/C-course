#include <math.h>
#include <complex.h>
#include "calculation.h"

roots calculation(double a, double b, double c)
{
    roots roots;
    if (fabs(a) > EPSILON)
        roots = quadratic_equation(a, b, c);
    else
        roots = linear_equation(b, c);
    roots = rounding(roots.x1, roots.x2);
    return roots;
}

roots quadratic_equation(double a, double b, double c)
{
    roots roots;
    double D = 0.0;
    D = b * b - 4 * a * c;
    roots.x1 = (-b - csqrt(D)) / (2 * a);
    roots.x2 = (-b + csqrt(D)) / (2 * a);
    return roots;
}

roots linear_equation(double b, double c)
{
    roots roots;
    roots.x1 = c / -b;
    roots.x2 = roots.x1;
    return roots;
}

roots rounding(double _Complex x1, double _Complex x2)
{
    roots roots;
    roots.x1 = x1;
    roots.x2 = x2;
    if (fabs(creal(roots.x1)) < EPSILON)
        roots.x1 = 0.0 + cimag(roots.x1)*I;
    if (fabs(creal(roots.x2)) < EPSILON)
        roots.x2 = 0.0 + cimag(roots.x2)*I;
    if (fabs(cimag(roots.x1)) < EPSILON)
        roots.x1 = 0.0 + creal(roots.x1);
    if (fabs(cimag(roots.x2)) < EPSILON)
        roots.x2 = 0.0 + creal(roots.x2);
    return roots;
}