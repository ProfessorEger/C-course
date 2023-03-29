/**
 \file
 \brief Contain declaration of functions to compare numbers
*/

#ifndef COMPARE_WITH_NUMBER_H
#define COMPARE_WITH_NUMBER_H
#include <stdbool.h>

static const double EPSILON = 1e-9; ///< Set a confidence interval
bool is_zero(double x); ///< Compare number with zero
bool compare(double _Complex num1, double _Complex num2); ///< Compare two numbers

#endif