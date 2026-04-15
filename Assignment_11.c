#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    long long fact = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    // a) Square root
    printf("Square root: %.2f\n", sqrt(n));

    // b) Square
    printf("Square: %d\n", n * n);

    // c) Cube
    printf("Cube: %d\n", n * n * n);

    // d) Prime check
    int isPrime = 1;
    if (n <= 1) isPrime = 0;
    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            isPrime = 0;
            break;
        }
    }

    if (isPrime)
        printf("Prime: Yes\n");
    else
        printf("Prime: No\n");

    // e) Factorial
    for (i = 1; i <= n; i++) {
        fact *= i;
    }
    printf("Factorial: %lld\n", fact);

    // f) Prime factors
    printf("Prime factors: ");
    int temp = n;
    for (i = 2; i <= temp; i++) {
        while (temp % i == 0) {
            printf("%d ", i);
            temp /= i;
        }
    }
    printf("\n");

    return 0;
}
