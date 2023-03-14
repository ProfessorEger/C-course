#include "solve_equation.h"
#include "read_print.h"

int main(void)
{
	quadratic_equation_coefficients coefficients = read_coefficients();
	solution roots = solve_equation(coefficients);
	print_solution(roots);
}