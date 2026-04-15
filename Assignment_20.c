#include <stdio.h>

// Call by value (no pointers)
void swap_value(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;

    printf("Inside swap_value: a = %d, b = %d\n", a, b);
}

// Call by reference (using pointers)
void swap_pointer(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    // Call by value
    swap_value(x, y);
    printf("After swap_value: x = %d, y = %d\n", x, y);

    // Call by reference
    swap_pointer(&x, &y);
    printf("After swap_pointer: x = %d, y = %d\n", x, y);

    return 0;
}