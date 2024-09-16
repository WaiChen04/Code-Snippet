#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

    FILE *fp = fopen(argv[1], "r"); /* FILE* aggregated type?*/

    if (fp == NULL)
    {
        printf("unable to open input file \n");
        exit(EXIT_SUCCESS);
    }

    int nrecords;

    fscanf(fp, "%d\n", &nrecords);

    int *array = malloc(sizeof(int) * nrecords);

    for (int i = 0; i < nrecords; i++)
    {
        fscanf(fp, "%d", &array[i]);
    }

    int nchecks;

    fscanf(fp, "%d", &nchecks);

    int product;

    int twoOrThree;

    for (int i = 0; i < nchecks; i++)
    {

        fscanf(fp, "%d", &product);
        fscanf(fp, "%d\n", &twoOrThree);

        char result[4] = "no";

        if (twoOrThree == 2)
        {
            for (int j = 0; j < nrecords; j++)
            {
                for (int k = 0; k < nrecords; k++)
                {
                    if (array[j] * array[k] == product && j != k)
                    {
                        strcpy(result, "yes");
                    }
                }
            }
        }

        if (twoOrThree == 3)
        {

            for (int l = 0; l < nrecords; l++)
            {

                for (int j = 0; j < nrecords; j++)
                {
                    for (int k = 0; k < nrecords; k++)
                    {
                        if (array[j] * array[k] * array[l] == product && j != k && l != k && j != l)
                        {
                            strcpy(result, "yes");
                        }
                    }
                }
            }
        }

        printf("%s\n", result);
    }

    fclose(fp);
    free(array);

    return EXIT_SUCCESS;
}