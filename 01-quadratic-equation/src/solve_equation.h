/**
 \file
 \brief Contain declarations of types and functions that used in solving equation
*/

#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H

/// Contain coefficients of quadratic equation
typedef struct quadratic_equation_coefficients
{
	/**
	 contain three real coefficients:

	 coefficient[0] - coefficient at x^2;

	 coefficient[1] - coefficient at x;

	 coefficient[2] - free term.
	 */
	double coefficient[3];
} quadratic_equation_coefficients;

/// Contain linear equation coefficients
typedef struct linear_equation_coeficients
{
	/**
	 contain two real coefficients:

	 coefficient[0] - coefficient at x;

	 coefficient[2] - free term.
	 */
	double coefficient[2];
} linear_equation_coeficients;

/// Contain the number of roots
typedef enum
{
	infinite_number_of_roots = -1,
	no_roots,
	one_root,
	two_roots
} number_of_roots;

/// Contain solution of quadratic equation
typedef struct equation_solution
{
	number_of_roots number_of_roots; ///< contain the number of roots equation
	double _Complex x[2];			 ///< contain contain complex values of roots
} equation_solution;

/**
 \brief Solve an equation with arbitrary coefficients

 use solve_quadratic or solve_linear to solve a specific type of equation.
 \param coefficients contain coefficients of equation
 \return contain solution to equation
*/
equation_solution solve_equation(quadratic_equation_coefficients coefficients);
/**
 \brief Solve quadratic an equation

 \param coefficients contain coefficients of equation
 \return contain solution to equation
*/
equation_solution solve_quadratic(quadratic_equation_coefficients coefficients);
/**
 \brief Solve quadratic an equation

 \param coefficients contain coefficients of equation
 \return contain solution to equation
*/
equation_solution solve_linear(linear_equation_coeficients coefficients);

#endif