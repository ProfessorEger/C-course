#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H
#include <stdbool.h>

typedef struct roots 
{
    double _Complex x1;
    double _Complex x2;
} roots;

static const double EPSILON = 1e-9;
double _Complex clamp_to_zero(double _Complex x);
roots solve_equation(double a, double b, double c);
roots solve_quadratic(double a, double b, double c);
roots solve_linear(double b, double c);
bool is_zero(double x);

#endif 