#include <math.h>
#include <complex.h>
#include "solve_equation.h"

roots solve_equation(double a, double b, double c)
{
    roots roots;
    if (is_zero(a))
        roots = solve_linear(b, c);
    else
        roots = solve_quadratic(a, b, c);
    roots.x1 = clamp_to_zero(roots.x1);
    roots.x2 = clamp_to_zero(roots.x2);
    return roots;
}

roots solve_quadratic(double a, double b, double c)
{
    double D = b * b - 4 * a * c;
    roots roots = {(-b - csqrt(D)) / (2 * a), (-b + csqrt(D)) / (2 * a)};
    return roots;
}

roots solve_linear(double b, double c)
{
    roots roots = {c / -b, roots.x1};
    return roots;
}

double _Complex clamp_to_zero(double _Complex x)
{
    if (is_zero(creal(x)))
        x = 0.0 + cimag(x) * I;
    if (is_zero(cimag(x)))
        x = 0.0 + creal(x);
    return x;
}

bool is_zero(double x)
{
    if (fabs(x) < EPSILON)
        return true;
    else
        return false;
}