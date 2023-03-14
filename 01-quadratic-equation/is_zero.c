#include <math.h>
#include "is_zero.h"

bool is_zero(double x)
{
	return (fabs(x) < EPSILON);
}