#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <ctype.h>
#include "calculation.h"

int main(void)
{
    roots roots;
    double a = 0, b = 0, c = 0;

    for (int input_check = 0; input_check == 0;) // Ввод коэффициентов
    {
        printf("Введите коэфициенты a, b, c\n");
        input_check = scanf("%lf %lf %lf", &a, &b, &c);
        char check_char = '\0';
        while (scanf("%c", &check_char), check_char != '\n')
        {
            if (!isblank(check_char))
            {
                input_check = 0;
            }
        }
        if (input_check == 3)
            break;
        printf("Коэфициенты введены неккоректно.\n\n");
    }

    roots = calculation(a, b, c);

        if (fabs(creal(roots.x1) - creal(roots.x2)) < EPSILON && fabs(cimag(roots.x1) - cimag(roots.x2)) < EPSILON)
            printf("x = %.3lf\n", creal(roots.x1));
        else
        {
            if (fabs(cimag(roots.x1)) < EPSILON && fabs(cimag(roots.x2)) < EPSILON)
                printf("x1 = %.3lf\nx2 = %.3lf\n", creal(roots.x1), creal(roots.x2));
            else
                printf("x1 = %.3lf %+.3lfi\nx2 = %.3lf %+.3lfi\n", creal(roots.x1), cimag(roots.x1), creal(roots.x2), cimag(roots.x2));
        }
}