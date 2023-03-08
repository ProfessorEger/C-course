#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include "solve_equation.h"

typedef struct coefficients 
{
    double a, b, c;
} coefficients;

coefficients input();
void output(roots roots);

#endif 