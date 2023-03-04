#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "calculation.h"

int main(void)
{
    roots roots;
    printf("Введите коэфициенты a, b, c\n");
    double a = 0, b = 0, c = 0;
    scanf("%lf %lf %lf", &a, &b, &c);
    roots = calculation(a, b, c);

    if (fabs(creal(roots.x1) - creal(roots.x2)) < EPSILON)
        printf("real_x1 = %lf\nreal_x2 = %lf\nimag_x1 = %lf\nimag_x2 = %lf\n", creal(roots.x1), creal(roots.x2), cimag(roots.x1), cimag(roots.x2));
        //printf("x = %lf\n", roots.real_x1);
    else
        printf("real_x1 = %lf\nreal_x2 = %lf\nimag_x1 = %lf\nimag_x2 = %lf\n", creal(roots.x1), creal(roots.x2) , cimag(roots.x1), cimag(roots.x2));
}