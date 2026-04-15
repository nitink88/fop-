#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char ch;

    // Open source file (read mode)
    fp1 = fopen("source.txt", "r");

    if (fp1 == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    // Open destination file (write mode)
    fp2 = fopen("destination.txt", "w");

    if (fp2 == NULL) {
        printf("Error opening destination file.\n");
        return 1;
    }

    // Copy contents character by character
    while ((ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);
    }

    printf("File copied successfully.\n");

    fclose(fp1);
    fclose(fp2);

    return 0;
}