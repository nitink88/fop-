#include <stdio.h>

int main() {
    int choice;
    int a, b, i;
    long long fact;
    int result;

    do {
        printf("\n--- Calculator ---\n");
        printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n");
        printf("5. Power (x^y)\n6. Factorial (x!)\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                printf("Result: %d\n", a + b);
                break;

            case 2:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                printf("Result: %d\n", a - b);
                break;

            case 3:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                printf("Result: %d\n", a * b);
                break;

            case 4:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                if (b == 0)
                    printf("Division by zero not allowed\n");
                else
                    printf("Result: %.2f\n", (float)a / b);
                break;

            case 5:
                printf("Enter base and exponent: ");
                scanf("%d %d", &a, &b);
                result = 1;
                for(i = 1; i <= b; i++) {
                    result *= a;
                }
                printf("Result: %d\n", result);
                break;

            case 6:
                printf("Enter a number: ");
                scanf("%d", &a);
                if (a < 0) {
                    printf("Factorial not defined for negative numbers\n");
                } else {
                    fact = 1;
                    for(i = 1; i <= a; i++) {
                        fact *= i;
                    }
                    printf("Result: %lld\n", fact);
                }
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while(choice != 7);

    return 0;
}
