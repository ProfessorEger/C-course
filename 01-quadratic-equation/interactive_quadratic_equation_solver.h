/**
 \file
 \brief Contain declarations of functions that used in user interaction
*/

#ifndef INTERACTIVE_QUADRATIC_EQUATION_SOLVER_H
#define INTERACTIVE_QUADRATIC_EQUATION_SOLVER_H
#include "solve_equation.h"

/**
 \brief Ask user for coefficients and read them
 \return equation coefficients
*/
quadratic_equation_coefficients read_coefficients();

void print_solution(equation_solution roots); ///< Display solution to equation
void print_roots(equation_solution roots);	  ///< Display roots to equation

#endif