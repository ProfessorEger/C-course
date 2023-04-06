#include "test_solve_equation.h"
#include "../compare_with_number.h"
//#include "../interactive_quadratic_equation_solver.h"
#include <complex.h>
#include <string.h>

int main(void)
{
	FILE *myfile;
	myfile = fopen("../test_solve_equation_config", "r");
	char word[SIZE_WORD];

	while (1)
	{
		fscanf(myfile, "%s", &*word);
		if (strcmp(word, "test_solve_equation") == 0)
			read_equation(myfile);
		else if (strcmp(word, "test_solve_quadratic") == 0)
			read_quadratic_equation(myfile);
		else if (strcmp(word, "test_solve_linear") == 0)
			read_linear_equation(myfile);
		else if (strcmp(word, "complete_tests") == 0)
			break;
	}
	fclose(myfile);
	return (0);
}

void read_equation(FILE *myfile)
{
	quadratic_equation equation;
	double real_x = 0;
	double imag_x = 0;
	char word[SIZE_WORD];
	short number_of_tests = 0;
	while (1)
	{
		fscanf(myfile, "%s", &*word);

		if (strcmp(word, "coeficients:") == 0)
			fscanf(myfile, "%lf%lf%lf", &equation.coefficients.coefficient[0], &equation.coefficients.coefficient[1], &equation.coefficients.coefficient[2]);
		else if (strcmp(word, "x1:") == 0)
		{
			fscanf(myfile, "%lf%lf", &real_x, &imag_x);
			equation.solution.x[0] = real_x + imag_x * I;
		}
		else if (strcmp(word, "x2:") == 0)
		{
			fscanf(myfile, "%lf%lf", &real_x, &imag_x);
			equation.solution.x[1] = real_x + imag_x * I;
		}
		else if (strcmp(word, "number_of_roots:") == 0)
		{
			fscanf(myfile, "%d", &equation.solution.number_of_roots);
			number_of_tests++;
			test_solve_equation(equation, number_of_tests);
		}
		else if (strcmp(word, "end_test") == 0)
			break;
	}
}

void read_quadratic_equation(FILE *myfile)
{
	quadratic_equation equation;
	double real_x = 0;
	double imag_x = 0;
	char word[SIZE_WORD];
	short number_of_tests = 0;
	while (1)
	{
		fscanf(myfile, "%s", &*word);

		if (strcmp(word, "coeficients:") == 0)
			fscanf(myfile, "%lf%lf%lf", &equation.coefficients.coefficient[0], &equation.coefficients.coefficient[1], &equation.coefficients.coefficient[2]);
		else if (strcmp(word, "x1:") == 0)
		{
			fscanf(myfile, "%lf%lf", &real_x, &imag_x);
			equation.solution.x[0] = real_x + imag_x * I;
		}
		else if (strcmp(word, "x2:") == 0)
		{
			fscanf(myfile, "%lf%lf", &real_x, &imag_x);
			equation.solution.x[1] = real_x + imag_x * I;
		}
		else if (strcmp(word, "number_of_roots:") == 0)
		{
			fscanf(myfile, "%d", &equation.solution.number_of_roots);
			number_of_tests++;
			test_solve_quadratic(equation, number_of_tests);
		}
		else if (strcmp(word, "end_test") == 0)
			break;
	}
}

void read_linear_equation(FILE *myfile)
{
	linear_equation equation;
	double real_x = 0;
	char word[SIZE_WORD];
	short number_of_tests = 0;
	while (1)
	{
		fscanf(myfile, "%s", &*word);

		if (strcmp(word, "coeficients:") == 0)
			fscanf(myfile, "%lf%lf", &equation.coefficients.coefficient[0], &equation.coefficients.coefficient[1]);
		else if (strcmp(word, "x:") == 0)
		{
			fscanf(myfile, "%lf", &real_x);
			equation.solution.x[0] = real_x + 0*I;
		}
		else if (strcmp(word, "number_of_roots:") == 0)
		{
			fscanf(myfile, "%d", &equation.solution.number_of_roots);
			number_of_tests++;
			test_solve_linear(equation, number_of_tests);
		}
		else if (strcmp(word, "end_test") == 0)
			break;
	}
}

bool test_solve_equation(quadratic_equation equation, short number_of_tests)
{
	equation_solution solution = solve_equation(equation.coefficients);
	/*
	printf("Истина:    ");
	print_solution(equation.solution);
	printf("Результат: ");
	print_solution(solution);
	*/

	bool test = true;
	if (solution.number_of_roots != equation.solution.number_of_roots)
		test = false;
	for (int i = 0; i < equation.solution.number_of_roots; i++)
	{
		if (!compare(solution.x[i], equation.solution.x[i]))
			test = false;
	}

	if (test)
		printf("test_solve_equation №%hd пройден\n", number_of_tests);
	else
		printf("test_solve_equation №%hd провален\n", number_of_tests);

	return test;
}

bool test_solve_linear(linear_equation equation, short number_of_tests)
{
	equation_solution solution = solve_linear(equation.coefficients);
	/*
	printf("Истина:    ");
	print_solution(equation.solution);
	printf("Результат: ");
	print_solution(solution);
	*/

	bool test = true;
	if (solution.number_of_roots != equation.solution.number_of_roots)
		test = false;
	for (int i = 0; i < equation.solution.number_of_roots; i++)
	{
		if (!compare(solution.x[i], equation.solution.x[i]))
			test = false;
	}

	if (test)
		printf("test_solve_linear №%hd пройден\n", number_of_tests);
	else
		printf("test_solve_linear №%hd провален\n", number_of_tests);

	return test;
}

bool test_solve_quadratic(quadratic_equation equation, short number_of_tests)
{
	equation_solution solution = solve_quadratic(equation.coefficients);
	/*
	printf("Истина:    ");
	print_solution(equation.solution);
	printf("Результат: ");
	print_solution(solution);
	*/;
	

	bool test = true;
	if (solution.number_of_roots != equation.solution.number_of_roots)
		test = false;
	for (int i = 0; i < equation.solution.number_of_roots; i++)
	{
		if (!compare(solution.x[i], equation.solution.x[i]))
			test = false;
	}

	if (test)
		printf("test_solve_quadratic №%hd пройден\n", number_of_tests);
	else
		printf("test_solve_quadratic №%hd провален\n", number_of_tests);

	return test;
}