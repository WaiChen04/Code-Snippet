#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n)
{
    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int determinant(int **matrix, int n)
{
    if (n == 1)
    { /* 1x1 case*/
        return matrix[0][0];
    }
    else if (n == 2)
    { /*2x2 case*/
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    else
    {
        int det = 0;
        int sign;
        for (int i = 0; i < n; i++)
        {
            
            if (i % 2 == 0)
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }
            int **subMatrix = allocMatrix(n - 1); /*populate subMatrix*/
            for (int j = 1; j < n; j++)
            {
                int k = 0;
                for (int l = 0; l < n; l++)
                {   
                    if (l != i)
                    {
                        subMatrix[j - 1][k] = matrix[j][l];
                        k++;
                    }
                    
                }
            }
            det += sign * matrix[0][i] * determinant(subMatrix, n - 1);
            freeMatrix(subMatrix, n - 1);
        }
        return det;
    }
}

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        return EXIT_SUCCESS;
    }

    int size;
    fscanf(fp, "%d\n", &size);

    int **matrix = allocMatrix(size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    fclose(fp);

    int det = determinant(matrix, size);
    printf("%d\n", det);

    freeMatrix(matrix, size);

    return EXIT_SUCCESS;
}
