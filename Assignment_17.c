#include <stdio.h>

// Function to calculate factorial
int factorial(int n) {
    int i, fact = 1;
    for (i = 1; i <= n; i++) {
        fact = fact * i;
    }
    return fact;
}

int main() {
    int n, i, sign = 1;
    float x, sum = 0;

    printf("Enter value of x (in radians): ");
    scanf("%f", &x);

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        int power = 2 * i - 1;  // 1,3,5,7...
        float term = sign * (pow(x, power) / factorial(power));
        sum = sum + term;
        sign = -sign; // alternate sign
    }

    printf("Sum of sine series = %f\n", sum);

    return 0;
}

