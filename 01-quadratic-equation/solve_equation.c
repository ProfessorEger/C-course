#include <math.h>
#include <complex.h>
#include "solve_equation.h"

solution solve_equation(quadratic_equation_coefficients coefficients)
{
	solution roots;
	if (is_zero(coefficients.a))
	{
		linear_equation_coeficients linear_coefficients = {coefficients.b, coefficients.c};
		linear_equation_solution linear_equation_root = solve_linear(linear_coefficients);
		roots.x1 = linear_equation_root.x;
	}
	else
	{
		quadratic_equation_solution quadratic_equation_roots = solve_quadratic(coefficients);
		roots.x1 = quadratic_equation_roots.x1;
		roots.x2 = quadratic_equation_roots.x2;
	}
	roots.number_of_roots = edge_case_check(roots, coefficients);
	roots.x1 = clamp_to_zero(roots.x1);
	roots.x2 = clamp_to_zero(roots.x2);
	return roots;
}

quadratic_equation_solution solve_quadratic(quadratic_equation_coefficients coefficients)
{
	double D = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;
	quadratic_equation_solution quadratic_equation_roots = {(-coefficients.b - csqrt(D)) / (2 * coefficients.a), (-coefficients.b + csqrt(D)) / (2 * coefficients.a)};
	return quadratic_equation_roots;
}

linear_equation_solution solve_linear(linear_equation_coeficients coefficients)
{
	linear_equation_solution linear_equation_root = {coefficients.c / -coefficients.b};
	return linear_equation_root;
}

int edge_case_check(solution roots, quadratic_equation_coefficients coefficients)
{
	if ((is_zero(creal(roots.x1) - creal(roots.x2)) && is_zero(cimag(roots.x1) - cimag(roots.x2))) || is_zero(coefficients.a))
		roots.number_of_roots = 1; // один корень
	else
		roots.number_of_roots = 2; // два корня
	if (is_zero(coefficients.a) && is_zero(coefficients.b) && is_zero(coefficients.c))
		roots.number_of_roots = -1; // бесконечно много решений
	if (is_zero(coefficients.a) && is_zero(coefficients.b) && !is_zero(coefficients.c))
		roots.number_of_roots = 0; // корней нет
	return roots.number_of_roots;
}

double _Complex clamp_to_zero(double _Complex x)
{
	if (is_zero(creal(x)))
		x = 0.0 + cimag(x) * I;
	if (is_zero(cimag(x)))
		x = 0.0 + creal(x);
	return x;
}