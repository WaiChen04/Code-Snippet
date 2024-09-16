#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cacheSearch(int **hashTable, int cacheSize, int setSize, int assocNum, int blockSize, char *cachePol,
                 int *memread, int *memwrite, int *cachehit, int *cachemiss, char op, int bits, int *time,
                 int *FIFOTable, int **lruTable)
{

    int Bexp = 0;
    int Sexp = 0;
    
    int setIndex =0;
    while (blockSize != 1)
    {
        blockSize = blockSize >> 1;
        Bexp++;
    }
    while (setSize != 1)
    {
        setSize = setSize >> 1;
        Sexp++;
    }

    bits = bits >> Bexp;
    if(Sexp != 0){
    int setMask = 1;

    for (int i = 1; i < Sexp; i++)
    {
        setMask = setMask << 1;
        setMask++;
    }




    setIndex = bits & setMask;
    }

    bits = bits >> Sexp; /*now the tag bits*/

    int IsFound = 0;

    for (int i = 0; i < assocNum; i++)
    {
        if (hashTable[setIndex][i] == bits)
        {
            IsFound = 1;
            (*cachehit)++;
            
                if (op == 'W')
                {
                    (*memwrite)++;
                }
            lruTable[setIndex][i] = *time;
        }
    }
    int IsEmpty = 0;
    if (IsFound == 0)
    {
        (*cachemiss)++;
        (*memread)++;

        for (int i = 0; i < assocNum; i++)
        {
            if (hashTable[setIndex][i] == -1)
            {
                IsEmpty = 1;
                hashTable[setIndex][i] = bits;
                lruTable[setIndex][i] = *time;


                if (op == 'W')
                {
                    (*memwrite)++;
                }
                FIFOTable[setIndex] = (FIFOTable[setIndex] + 1) % assocNum;
                break;
            }
        }
            if (IsEmpty == 0)
            {

                if (strcmp(cachePol, "fifo") == 0)
                {

                    hashTable[setIndex][FIFOTable[setIndex]] = bits;
                    lruTable[setIndex][FIFOTable[setIndex]] = *time;
                    if (op == 'W')
                    {
                        (*memwrite)++;
                    }
                    FIFOTable[setIndex] = (FIFOTable[setIndex] + 1) % assocNum;
                }
                if (strcmp(cachePol, "lru") == 0)
                {

                    int lessvalue = lruTable[setIndex][0];
                    int lessIndex = 0;
                    for (int i = 0; i < assocNum; i++)
                    {
                        if (lessvalue > lruTable[setIndex][i])
                        {
                            lessvalue = lruTable[setIndex][i];
                            lessIndex = i;
                        }
                    }
                    hashTable[setIndex][lessIndex] = bits;

                    if (op == 'W')
                    {
                        (*memwrite)++;
                    }

                    lruTable[setIndex][lessIndex] = *time;
                }
            
        }
    }
    (*time)++;


}

int main(int argc, char **argv)
{

    int cacheSize = strtoul(argv[1], NULL, 10);
    char *assoc = argv[2];
    int assocNum;
    char *cachePol = argv[3];
    int blockSize = strtoul(argv[4], NULL, 10);
    ;

    sscanf(assoc, "assoc:%d", &assocNum);


    int setSize = (cacheSize / (assocNum * blockSize));




    int **hashTable = malloc(setSize * sizeof(int *));

    for (int i = 0; i < setSize; i++)
    {
        hashTable[i] = malloc(assocNum * sizeof(int));
    }
    for (int i = 0; i < setSize; i++)
    {
        for (int j = 0; j < assocNum; j++)
        {
            hashTable[i][j] = -1;
        }
    }

        int *FIFOTable = malloc(setSize * sizeof(int *));

    for (int i = 0; i < setSize; i++)
    {
        FIFOTable[i] = 0;
    }

    int **lruTable = malloc(setSize * sizeof(int *));

    for (int i = 0; i < setSize; i++)
    {
        lruTable[i] = malloc(assocNum * sizeof(int));
    }

    for (int i = 0; i < setSize; i++)
    {
        for (int j = 0; j < assocNum; j++)
        {
            lruTable[i][j] = -1;
        }
    }

    FILE *fp = fopen(argv[5], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    int memread = 0;
    int memwrite = 0;
    int cachehit = 0;
    int cachemiss = 0;

    char op;
    int bits;

    int time = 0;



    while (fscanf(fp, "%c %x", &op, &bits) == 2)
    {
        cacheSearch(hashTable, cacheSize, setSize, assocNum, blockSize, cachePol, &memread, &memwrite, &cachehit, &cachemiss, op, bits, &time, FIFOTable, lruTable);
        fscanf(fp, "%*[^\n]");
            fgetc(fp);

    }

    printf("memread:%d\n", memread);
  printf("memwrite:%d\n", memwrite);
    printf("cachehit:%d\n", cachehit);
  printf("cachemiss:%d\n", cachemiss);

    fclose(fp);

    for (int i = 0; i < setSize; i++)
    {
        free(hashTable[i]);
    }
    free(hashTable);


    for (int i = 0; i < setSize; i++)
    {
        free(lruTable[i]);
    }
    free(lruTable);

    free(FIFOTable);

    return EXIT_SUCCESS;
}
