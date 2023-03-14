#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H
#include "is_zero.h"

typedef struct quadratic_equation_coefficients
{
	double a, b, c;
} quadratic_equation_coefficients;

typedef struct linear_equation_coeficients
{
	double b, c;
} linear_equation_coeficients;

typedef struct quadratic_equation_solution
{
	double _Complex x1, x2;
} quadratic_equation_solution;

typedef struct linear_equation_solution
{
	double x;
} linear_equation_solution;

typedef struct solution
{
	int number_of_roots;
	/*
	Если number_of_roots =
	1, 2: количество кроней
	0	: корней нет
	-1	: Корней бесконечно много
	-2	: Корни неопределены
	*/
	double _Complex x1, x2;
} solution;

double _Complex clamp_to_zero(double _Complex x);
solution solve_equation(quadratic_equation_coefficients coefficients);
quadratic_equation_solution solve_quadratic(quadratic_equation_coefficients coefficients);
linear_equation_solution solve_linear(linear_equation_coeficients coefficients);
int edge_case_check(solution roots, quadratic_equation_coefficients coefficients);

#endif