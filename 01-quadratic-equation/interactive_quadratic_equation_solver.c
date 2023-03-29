#include "interactive_quadratic_equation_solver.h"
#include "compare_with_number.h"
#include <stdio.h>
#include <ctype.h>
#include <complex.h>

quadratic_equation_coefficients read_coefficients()
{
	quadratic_equation_coefficients coefficients = {0, 0, 0};
	while (1) // Ввод коэффициентов
	{
		puts("Введите коэфициенты a, b, c");
		int input_check = scanf("%lf %lf %lf", &coefficients.coefficient[0], &coefficients.coefficient[1], &coefficients.coefficient[2]);
		char check_char = '\0';
		while (scanf("%c", &check_char), check_char != '\n')
		{
			if (!isblank(check_char))
				input_check = 0;
		}
		if (input_check == 3)
			break;
		puts("Коэфициенты введены неккоректно.");
	}
	return coefficients;
}

void print_solution(equation_solution roots)
{
	switch (roots.number_of_roots)
	{
	case one_root:
	case two_roots:
		print_roots(roots);
		break;
	case no_roots:
		puts("Корней нет");
		break;
	case infinite_number_of_roots:
		puts("Бесконечно много решений");
		break;
	}
}

void print_roots(equation_solution roots)
{
	printf("solution: (");
	for (int i = 0; i < roots.number_of_roots; i++)
	{
		if (!is_zero(creal(roots.x[i])))
			printf("%.3lf", creal(roots.x[i]));
		if (!is_zero(creal(roots.x[i])) && !is_zero(cimag(roots.x[i])))
			printf(" %+.3lfi", cimag(roots.x[i]));
		else if (is_zero(creal(roots.x[i])) && !is_zero(cimag(roots.x[i])))
			printf("%.3lfi", cimag(roots.x[i]));
		if (i + 1 < roots.number_of_roots)
			printf(", ");
	}
	puts(")");
}