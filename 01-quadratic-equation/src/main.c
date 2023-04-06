#include "solve_equation.h"
#include "interactive_quadratic_equation_solver.h"

int main(void)
{
	quadratic_equation_coefficients coefficients = read_coefficients();
	equation_solution roots = solve_equation(coefficients);
	print_solution(roots);
}