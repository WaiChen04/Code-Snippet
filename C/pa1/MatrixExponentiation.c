#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void multiple(int **result, int **matrix, int **matrixT, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result[i][j] = 0;
            for (int l = 0; l < size; l++)
            {
                result[i][j] += matrix[i][l] * matrixT[j][l];
            }
        }
    }
}

void shiftMatrix(int **target, int **copy, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            target[i][j] = copy[i][j];
        }
    }
}

int main(int argc, char **argv)
{

    FILE *fp = fopen(argv[1], "r"); /* FILE* aggregated type?*/

    if (fp == NULL)
    {
        printf("unable to open input file \n");
        exit(EXIT_SUCCESS);
    }

    int size;

    fscanf(fp, "%d\n", &size);

    int **matrix = allocMatrix(size);

    for (int i = 0; i < size; i++)
    { /*Build matrix*/
        for (int j = 0; j < size; j++)
        {
            if (j == (size - 1))
            {
                fscanf(fp, "%d\n", &matrix[i][j]);
            }
            else
            {
                fscanf(fp, "%d\n", &matrix[i][j]);
            }
        }
    }

    int power;
    fscanf(fp, "%d\n", &power);

    int **matrixT = allocMatrix(size);

    for (int i = 0; i < size; i++)
    { /*Build matrix Transposed*/
        for (int j = 0; j < size; j++)
        {
            matrixT[j][i] = matrix[i][j];
        }
    }

    int **result = allocMatrix(size);

    if (power > 1)
    {

        for (int i = 1; i < power; i++)
        {
            multiple(result, matrix, matrixT, size);
            shiftMatrix(matrix, result, size);
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d\t", result[i][j]);
            }
            printf("\n");
        }
    }
    else
    {

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
        }
    }

    fclose(fp);
    freeMatrix(matrix, size);
    freeMatrix(matrixT, size);
    freeMatrix(result, size);

    return EXIT_SUCCESS;
}