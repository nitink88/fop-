#include <stdio.h>
#include <math.h>

int main() {
    int binary, decimal = 0, remainder, i = 0;

    printf("Enter a binary number: ");
    scanf("%d", &binary);

    while (binary != 0) {
        remainder = binary % 10;
        decimal = decimal + remainder * pow(2, i);
        binary = binary / 10;
        i++;
    }

    printf("Decimal equivalent: %d", decimal);

    return 0;
}