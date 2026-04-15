#include <stdio.h>

int main() {
    int n, original, rem;
    int sum = 0;

    printf("Enter a 3-digit number: ");
    scanf("%d", &n);

    original = n;

    while (n > 0) {
        rem = n % 10;
        sum = sum + (rem * rem * rem);
        n = n / 10;
    }

    if (sum == original)
        printf("Armstrong number\n");
    else
        printf("Not an Armstrong number\n");

    return 0;
}
