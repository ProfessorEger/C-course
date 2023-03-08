#include "solve_equation.h"
#include "input_output.h"

int main(void)
{
    coefficients coefficients = input();
    roots roots = solve_equation(coefficients.a, coefficients.b, coefficients.c);
    output(roots);
}