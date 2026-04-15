#include <stdio.h>

// Function to calculate length
int length(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

// Function to reverse string
void reverse(char str[]) {
    int i, len = length(str);
    char temp;

    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to compare strings
int compare(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 0;
        }
        i++;
    }
    return (s1[i] == s2[i]);
}

// Function to check palindrome
int palindrome(char str[]) {
    int i, len = length(str);
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// Function to check substring
int substring(char str[], char sub[]) {
    int i, j;
    for (i = 0; str[i] != '\0'; i++) {
        j = 0;
        while (sub[j] != '\0' && str[i + j] == sub[j]) {
            j++;
        }
        if (sub[j] == '\0') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char str1[100], str2[100], sub[100];

    printf("Enter main string: ");
    scanf("%s", str1);

    printf("Enter second string (for comparison): ");
    scanf("%s", str2);

    printf("Enter substring: ");
    scanf("%s", sub);

    // Length
    printf("Length of string: %d\n", length(str1));

    // Reverse
    reverse(str1);
    printf("Reversed string: %s\n", str1);

    // Compare
    if (compare(str1, str2))
        printf("Strings are equal\n");
    else
        printf("Strings are not equal\n");

    // Palindrome
    if (palindrome(str1))
        printf("String is a palindrome\n");
    else
        printf("String is not a palindrome\n");

    // Substring
    if (substring(str1, sub))
        printf("Substring found\n");
    else
        printf("Substring not found\n");

    return 0;
}
