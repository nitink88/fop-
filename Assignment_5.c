#include <stdio.h>

int main() {
    int choice, i, j;
    int a[10][10], b[10][10], c[10][10];
    int r, col;

    printf("\nMatrix Operations Menu\n");
    printf("1. Addition of two matrices\n");
    printf("2. Saddle point of a matrix\n");
    printf("3. Inverse of a 2x2 matrix\n");
    printf("4. Magic square check\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {

        case 1: // Matrix Addition
            printf("Enter rows and columns: ");
            scanf("%d %d", &r, &col);

            printf("Enter first matrix:\n");
            for(i=0;i<r;i++)
                for(j=0;j<col;j++)
                    scanf("%d",&a[i][j]);

            printf("Enter second matrix:\n");
            for(i=0;i<r;i++)
                for(j=0;j<col;j++)
                    scanf("%d",&b[i][j]);

            printf("Result matrix:\n");
            for(i=0;i<r;i++){
                for(j=0;j<col;j++){
                    c[i][j] = a[i][j] + b[i][j];
                    printf("%d ",c[i][j]);
                }
                printf("\n");
            }
            break;

        case 2: // Saddle Point
            printf("Enter rows and columns: ");
            scanf("%d %d",&r,&col);

            printf("Enter matrix:\n");
            for(i=0;i<r;i++)
                for(j=0;j<col;j++)
                    scanf("%d",&a[i][j]);

            for(i=0;i<r;i++){
                int min = a[i][0], colIndex = 0;

                for(j=1;j<col;j++){
                    if(a[i][j] < min){
                        min = a[i][j];
                        colIndex = j;
                    }
                }

                int saddle = 1;
                for(j=0;j<r;j++){
                    if(a[j][colIndex] > min){
                        saddle = 0;
                        break;
                    }
                }

                if(saddle){
                    printf("Saddle Point: %d\n",min);
                    return 0;
                }
            }

            printf("No Saddle Point found\n");
            break;

        case 3: // Inverse of 2x2
            float m[2][2], det, inv[2][2];

            printf("Enter 2x2 matrix:\n");
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    scanf("%f",&m[i][j]);

            det = (m[0][0]*m[1][1]) - (m[0][1]*m[1][0]);

            if(det == 0){
                printf("Inverse not possible\n");
            } else {
                inv[0][0] = m[1][1]/det;
                inv[0][1] = -m[0][1]/det;
                inv[1][0] = -m[1][0]/det;
                inv[1][1] = m[0][0]/det;

                printf("Inverse matrix:\n");
                for(i=0;i<2;i++){
                    for(j=0;j<2;j++)
                        printf("%.2f ",inv[i][j]);
                    printf("\n");
                }
            }
            break;

        case 4: // Magic Square
            int n, sum=0, rowSum, colSum, diag1=0, diag2=0;
            int magic[10][10];

            printf("Enter order of square matrix: ");
            scanf("%d",&n);

            printf("Enter matrix:\n");
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    scanf("%d",&magic[i][j]);

            for(j=0;j<n;j++)
                sum += magic[0][j];

            int magicFlag = 1;

            for(i=0;i<n;i++){
                rowSum = 0;
                colSum = 0;

                for(j=0;j<n;j++){
                    rowSum += magic[i][j];
                    colSum += magic[j][i];
                }

                if(rowSum != sum || colSum != sum)
                    magicFlag = 0;
            }

            for(i=0;i<n;i++){
                diag1 += magic[i][i];
                diag2 += magic[i][n-i-1];
            }

            if(diag1 != sum || diag2 != sum)
                magicFlag = 0;

            if(magicFlag)
                printf("It is a Magic Square\n");
            else
                printf("Not a Magic Square\n");

            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}
