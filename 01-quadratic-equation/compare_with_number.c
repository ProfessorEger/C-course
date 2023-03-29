#include "compare_with_number.h"
#include <complex.h>
#include <math.h>

bool is_zero(double x)
{
	return (fabs(x) < EPSILON);
}

bool compare(double _Complex num1, double _Complex num2)
{
	return (is_zero(creal(num1) - creal(num2)) && is_zero(cimag(num1) - cimag(num2)));
}