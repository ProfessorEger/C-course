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