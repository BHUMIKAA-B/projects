#include <stdio.h>

int main() {
    char operator;
    double num1, num2;
    char choice;

    do {
        printf("Enter an operator (+, -, *, /): ");
        scanf(" %c", &operator);

        printf("Enter two numbers: ");
        scanf("%lf %lf", &num1, &num2);

        switch(operator) {
            case '+':
                printf("Result = %.2lf\n", num1 + num2);
                break;
            case '-':
                printf("Result = %.2lf\n", num1 - num2);
                break;
            case '*':
                printf("Result = %.2lf\n", num1 * num2);
                break;
            case '/':
                if (num2 != 0)
                    printf("Result = %.2lf\n", num1 / num2);
                else
                    printf("Error: Division by zero not allowed!\n");
                break;
            default:
                printf("Invalid operator!\n");
        }

        printf("Do you want to perform another calculation? (y/n): ");
        scanf(" %c", &choice);
    } while(choice == 'y' || choice == 'Y');

    printf("Calculator closed. Goodbye!\n");
    return 0;
}