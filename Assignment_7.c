#include <stdio.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

int main() {
    struct Student s[3];
    int i;

    // Input details
    for (i = 0; i < 3; i++) {
        printf("\nEnter details of student %d:\n", i + 1);

        printf("Roll number: ");
        scanf("%d", &s[i].roll);

        printf("Name: ");
        scanf("%s", s[i].name);

        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    // Display result
    printf("\nStudent Results:\n");
    for (i = 0; i < 3; i++) {
        printf("\nRoll: %d", s[i].roll);
        printf("\nName: %s", s[i].name);
        printf("\nMarks: %.2f", s[i].marks);

        if (s[i].marks >= 40)
            printf("\nResult: Pass\n");
        else
            printf("\nResult: Fail\n");
    }

    return 0;
}
