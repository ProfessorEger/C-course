// Квадратное уравнение прототип
#include <stdio.h>
#include <math.h>
#include <complex.h>

int main(void)
{

    double a, b, c;         // a - коэфициент при x^2; b - коєфициент при x; c - свободный член
    double D;               // дискриминант
    double _Complex x1, x2; // крони

    printf("Введите коэфициенты a, b, c\n");
    int imput_check = scanf("%lf %lf %lf", &a, &b, &c);

    if (imput_check == 3)
    {
        if (a >= 0.000000001 || a <= -0.000000001)
        {
            D = b * b - 4 * a * c;
            printf("D = %lf\n", D);
            x1 = (-b + 0 - csqrt(D)) / (2 * a);
            x2 = (-b + csqrt(D)) / (2 * a);

            if (D > 0) // Вывод в случае корректного введения коэфициентов
                printf("x1 = %.3lf\nx2 = %.3lf\n", creal(x1), creal(x2));
            else if (D <= 0.0000001 && D >= -0.0000001)
                printf("x = %.3lf\n", creal(x1));
            else
                printf("x1 = %.3lf - %.3lfi\nx2 = %.3lf + %.3lfi\n", creal(x1), cimag(x2), creal(x2), cimag(x2));
        }
        else if (b >= 0.000000001 || b <= -0.000000001) // a=0; b!=0
        {
            x1 = -c / b + 0;
            printf("x = %.3lf\n", creal(x1));
        }
        else if (c >= 0.000000001 || c <= -0.000000001) // a=0; b=0; c!=0
            printf("Корней нет\n");
        else // a=0; b=0; c=0
            printf("бесконечное множество решений\n");
    }
    else
        printf("Коэфициенты введены неккоректно\n");

    return 0;
}