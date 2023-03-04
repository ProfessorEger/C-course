#ifndef CALCULATION_H
#define CALCULATION_H

typedef struct roots 
{
    double _Complex x1;
    double _Complex x2;
} roots;

static const double EPSILON = 1e-9;
roots calculation(double a, double b, double c);
roots quadratic_equation(double a, double b, double c);
roots linear_equation(double b, double c);

#endif 