#ifndef TEST_SOLVE_EQUATION_H
#define TEST_SOLVE_EQUATION_H
#include "../solve_equation.h"
#include <stdbool.h>
#include <stdio.h>

const short SIZE_WORD = 30;

typedef struct quadratic_equation
{
quadratic_equation_coefficients coefficients;
equation_solution solution;
} quadratic_equation;

typedef struct linear_equation
{
linear_equation_coeficients coefficients;
equation_solution solution;
} linear_equation;

typedef struct word
{
	char word[SIZE_WORD];
} word;

void read_equation(FILE *myfile);
void read_quadratic_equation(FILE *myfile);
void read_linear_equation(FILE *myfile);
bool test_solve_quadratic(quadratic_equation equation, short number_of_tests);
bool test_solve_linear(linear_equation equation, short number_of_tests);
bool test_solve_equation(quadratic_equation equation, short number_of_tests);

#endif