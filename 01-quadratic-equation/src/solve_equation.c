#include "solve_equation.h"
#include "compare_with_number.h"
#include <math.h>
#include <complex.h>
#include <assert.h>

equation_solution solve_equation(quadratic_equation_coefficients coefficients)
{
	for (short i = 0; i < 3; i++)
	{
		assert(!isnan(coefficients.coefficient[i]) && "Коэффициент не может быть NaN");
		assert(!isinf(coefficients.coefficient[i]) && "Коэффициент не может быть inf");
	}

	equation_solution roots;
	if (is_zero(coefficients.coefficient[0]))
	{
		linear_equation_coeficients linear_coefficients = {coefficients.coefficient[1], coefficients.coefficient[2]};
		roots = solve_linear(linear_coefficients);
	}
	else
	{
		roots = solve_quadratic(coefficients);
	}
	return roots;
}

equation_solution solve_quadratic(quadratic_equation_coefficients coefficients)
{
	double D = coefficients.coefficient[1] * coefficients.coefficient[1] - 4 * coefficients.coefficient[0] * coefficients.coefficient[2];
	equation_solution quadratic_equation_roots;
	quadratic_equation_roots.x[0] = (-coefficients.coefficient[1] - csqrt(D)) / (2 * coefficients.coefficient[0]);
	quadratic_equation_roots.x[1] = (-coefficients.coefficient[1] + csqrt(D)) / (2 * coefficients.coefficient[0]);
	if (is_zero(D))
		quadratic_equation_roots.number_of_roots = one_root; // один корень
	else
		quadratic_equation_roots.number_of_roots = two_roots; // два корня
	return quadratic_equation_roots;
}

equation_solution solve_linear(linear_equation_coeficients coefficients)
{
	equation_solution linear_equation_root;
	linear_equation_root.x[0] = coefficients.coefficient[1] / -coefficients.coefficient[0];
	if (is_zero(coefficients.coefficient[0]) && is_zero(coefficients.coefficient[1]))
		linear_equation_root.number_of_roots = infinite_number_of_roots; // бесконечно много корней
	else if (is_zero(coefficients.coefficient[0]) && !is_zero(coefficients.coefficient[1]))
		linear_equation_root.number_of_roots = no_roots; // корней нет
	else
		linear_equation_root.number_of_roots = one_root; // один корень
	return linear_equation_root;
}
