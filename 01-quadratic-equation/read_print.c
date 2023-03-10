#include <stdio.h>
#include <ctype.h>
#include <complex.h>
#include "read_print.h"

quadratic_equation_coefficients read_coefficients()
{
	quadratic_equation_coefficients coefficients = {0, 0, 0};
	while (1) // Ввод коэффициентов
	{
		printf("Введите коэфициенты a, b, c\n");
		int input_check = scanf("%lf %lf %lf", &coefficients.a, &coefficients.b, &coefficients.c);
		char check_char = '\0';
		while (scanf("%c", &check_char), check_char != '\n')
		{
			if (!isblank(check_char))
				input_check = 0;
		}
		if (input_check == 3)
			break;
		printf("Коэфициенты введены неккоректно.\n\n");
	}
	return coefficients;
}

void print_solution(solution roots)
{
	switch (roots.number_of_roots)
	{
	case 1:
		printf("x = %.3f\n", creal(roots.x1));
		break;
	case 2:
		if (is_zero(cimag(roots.x1)))
			printf("x1 = %.3lf\nx2 = %.3lf\n", creal(roots.x1), creal(roots.x2));
		else
			printf("x1 = %.3lf %+.3lfi\nx2 = %.3lf %+.3lfi\n", creal(roots.x1), cimag(roots.x1), creal(roots.x2), cimag(roots.x2));
		break;
	case 0:
		printf("Корней нет\n");
		break;
	case -1:
		printf("Бесконечно много решений\n");
		break;
	case -2:
		printf("Решить невозможно\n");
		break;
	}
}