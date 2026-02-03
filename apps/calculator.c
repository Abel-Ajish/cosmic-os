#include <stdio.h>
#include <stdlib.h>

int main() {
    char op;
    double first, second;
    printf("cosmic-calc > Enter an operator (+, -, *, /): ");
    scanf("%c", &op);
    printf("cosmic-calc > Enter two operands: ");
    scanf("%lf %lf", &first, &second);

    switch (op) {
    case '+':
        printf("%.1lf + %.1lf = %.1lf\n", first, second, first + second);
        break;
    case '-':
        printf("%.1lf - %.1lf = %.1lf\n", first, second, first - second);
        break;
    case '*':
        printf("%.1lf * %.1lf = %.1lf\n", first, second, first * second);
        break;
    case '/':
        if (second != 0)
            printf("%.1lf / %.1lf = %.1lf\n", first, second, first / second);
        else
            printf("Error! Division by zero.\n");
        break;
    default:
        printf("Error! Operator is not correct\n");
    }

    return 0;
}
