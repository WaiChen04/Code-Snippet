#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cacheSearch(unsigned long **hashTable1, long cacheSize1, long setSize1, long assocNum1, long blockSize1, char *cachePol1,
                 long *memread, long *memwrite, long *cachehit1, long *cachemiss1, char op, unsigned long bits, long *time,
                 long **FIFOTable1, long **lruTable1,
                 unsigned long **hashTable2, long cacheSize2, long setSize2, long assocNum2, char *cachePol2,
                 long **FIFOTable2, long **lruTable2, long *cachehit2, long *cachemiss2, long *thInsert)
{

    if (op == 'W')
    {
        (*memwrite)++;
    }
    unsigned long oriBits = bits;

    long Bexp1 = 0;
    long Sexp1 = 0;

    long setMask2 = 1;

    long setIndex1 = 0;
    while (blockSize1 != 1)
    {
        blockSize1 = blockSize1 >> 1;
        Bexp1++;
    }
    while (setSize1 != 1)
    {
        setSize1 = setSize1 >> 1;
        Sexp1++;
    }

    unsigned long tag1 = bits >> Bexp1;
    if (Sexp1 != 0)
    {
        long setMask1 = 1;

        for (long i = 1; i < Sexp1; i++)
        {
            setMask1 = setMask1 << 1;
            setMask1++;
        }

        setIndex1 = tag1 & setMask1;
    }

    tag1 = tag1 >> Sexp1; /*now the tag bits*/

    long IsFound1 = 0;

    for (long i = 0; i < assocNum1; i++) /* If the
block is found in L1 cache, then the data is read from L1 cach*/
    {
        if (hashTable1[setIndex1][i] == tag1)
        {
            IsFound1 = 1;
            (*cachehit1)++;

            lruTable1[setIndex1][i] = *time;
            break;
        }
    }
    long IsEmpty1 = 0;
    if (IsFound1 == 0) /*. If the block is not found in the
 L1 cache, but present in the L2 cache, then the cache block is moved from the L2 cache to the L1
 cache. */
    {
        (*cachemiss1)++;

        bits = oriBits;

        long Sexp2 = 0;

        long setIndex2 = 0;

        while (setSize2 != 1)
        {
            setSize2 = setSize2 >> 1;
            Sexp2++;
        }

        unsigned long tag2 = bits >> Bexp1;
        if (Sexp2 != 0)
        {
            setMask2 = 1;

            for (long i = 1; i < Sexp2; i++)
            {
                setMask2 = setMask2 << 1;
                setMask2++;
            }

            setIndex2 = tag2 & setMask2;
        }

        tag2 = tag2 >> Sexp2; /*now the tag bits*/
        long IsFound2 = 0;

        for (long i = 0; i < assocNum2; i++) /* If the
    block is found in L1 cache, then the data is read from L1 cach*/
        {
            if (hashTable2[setIndex2][i] == tag2) /*then the cache block is moved from the L2 cache to the L1
    cache*/
            {
                IsFound2 = 1;
                (*cachehit2)++;

                lruTable2[setIndex2][i] = 0;

                hashTable2[setIndex2][i] = '\0';
                FIFOTable2[setIndex2][i] = -1;


                break;
            }
        }
        if (IsFound2 == 0)
        {
            (*cachemiss2)++;
            (*memread)++;
        }
        /*check if L1 is empty and fill it in*/
        for (long i = 0; i < assocNum1; i++)
        {
            if (hashTable1[setIndex1][i] == '\0')
            {
                IsEmpty1 = 1;
                hashTable1[setIndex1][i] = tag1;
                lruTable1[setIndex1][i] = *time;
                FIFOTable1[setIndex1][i] = *thInsert;
                (*thInsert)++;


                break;
            }
        }

        if (IsEmpty1 == 0)
        {

            unsigned long evictedtag1 = 0;
            if (strcmp(cachePol1, "fifo") == 0)
            {

                long lessvalue = FIFOTable1[setIndex1][0];
                long lessIndex = 0;
                for (long i = 0; i < assocNum1; i++)
                {
                    if (lessvalue > FIFOTable1[setIndex1][i])
                    {
                        lessvalue = FIFOTable1[setIndex1][i];
                        lessIndex = i;
                    }
                }
                evictedtag1 = hashTable1[setIndex1][lessIndex];
                hashTable1[setIndex1][lessIndex] = tag1;
                FIFOTable1[setIndex1][lessIndex] = *thInsert;
                (*thInsert)++;
            }
            if (strcmp(cachePol1, "lru") == 0)
            {

                long lessvalue = lruTable1[setIndex1][0];
                long lessIndex = 0;
                for (long i = 0; i < assocNum1; i++)
                {
                    if (lessvalue > lruTable1[setIndex1][i])
                    {
                        lessvalue = lruTable1[setIndex1][i];
                        lessIndex = i;
                    }
                }
                evictedtag1 = hashTable1[setIndex1][lessIndex];
                hashTable1[setIndex1][lessIndex] = tag1;
                lruTable1[setIndex1][lessIndex] = *time;
            }
            /*now have to place the evicted tag in L2*/

            unsigned long evictedbits = (evictedtag1 << Sexp1) | setIndex1;

            long evictedsetIndex2 = 0;
            if (Sexp2 != 0)
            {
                evictedsetIndex2 = evictedbits & setMask2;
                
            }

            unsigned long evictedtag2 = evictedbits >> Sexp2;

            long IsEmpty2 = 0;
            for (long i = 0; i < assocNum2; i++)
            {
                if (hashTable2[evictedsetIndex2][i] == '\0')
                {
                    IsEmpty2 = 1;
                    hashTable2[evictedsetIndex2][i] = evictedtag2;
                    lruTable2[evictedsetIndex2][i] = *time;

                FIFOTable2[evictedsetIndex2][i] = *thInsert;
                (*thInsert)++;
                    break;
                }
            }
            if (IsEmpty2 == 0)
            {
                if (strcmp(cachePol2, "fifo") == 0)
                {
                    long lessvalue = FIFOTable2[evictedsetIndex2][0];
                    long lessIndex = 0;
                    for (long i = 0; i < assocNum2; i++)
                    {
                        if (lessvalue > FIFOTable2[evictedsetIndex2][i])
                        {
                            lessvalue = FIFOTable2[evictedsetIndex2][i];
                            lessIndex = i;
                        }
                    }
                    hashTable2[evictedsetIndex2][lessIndex] = evictedtag2;
                    FIFOTable2[evictedsetIndex2][lessIndex] = *thInsert;
                    (*thInsert)++;
                    

                }
                if (strcmp(cachePol2, "lru") == 0)
                {

                    long lessvalue = lruTable2[evictedsetIndex2][0];
                    long lessIndex = 0;
                    for (long i = 0; i < assocNum2; i++)
                    {
                        if (lessvalue > lruTable2[evictedsetIndex2][i])
                        {
                            lessvalue = lruTable2[evictedsetIndex2][i];
                            lessIndex = i;
                        }
                    }
                    hashTable2[evictedsetIndex2][lessIndex] = evictedtag2;
                    lruTable2[evictedsetIndex2][lessIndex] = *time;
                }
            }
        }
    }
    (*time)++;
}

int main(int argc, char **argv)
{

    long cacheSize1 = strtoul(argv[1], NULL, 10);
    char *assoc1 = argv[2];
    long assocNum1;
    char *cachePol1 = argv[3];
    long blockSize1 = strtoul(argv[4], NULL, 10);
    sscanf(assoc1, "assoc:%ld", &assocNum1);
    long setSize1 = (cacheSize1 / (assocNum1 * blockSize1));

    long cacheSize2 = strtoul(argv[5], NULL, 10);
    char *assoc2 = argv[6];
    long assocNum2;
    char *cachePol2 = argv[7];
    sscanf(assoc2, "assoc:%ld", &assocNum2);
    long setSize2 = (cacheSize2 / (assocNum2 * blockSize1));

    unsigned long **hashTable1 = malloc(setSize1 * sizeof(unsigned long *));

    for (long i = 0; i < setSize1; i++)
    {
        hashTable1[i] = malloc(assocNum1 * sizeof(unsigned long));
    }
    for (long i = 0; i < setSize1; i++)
    {
        for (long j = 0; j < assocNum1; j++)
        {
            hashTable1[i][j] = '\0';
        }
    }

    long **FIFOTable1 = malloc(setSize1 * sizeof(long *));


    for (long i = 0; i < setSize1; i++)
    {
        FIFOTable1[i] = malloc(assocNum1 * sizeof(unsigned long));
    }

    for (long i = 0; i < setSize1; i++)

    {
        for(long j = 0; j <assocNum1; j++){
        FIFOTable1[i][j] = -1;
        }
    }

    long **lruTable1 = malloc(setSize1 * sizeof(long *));

    for (long i = 0; i < setSize1; i++)
    {
        lruTable1[i] = malloc(assocNum1 * sizeof(long));
    }

    for (long i = 0; i < setSize1; i++)
    {
        for (long j = 0; j < assocNum1; j++)
        {
            lruTable1[i][j] = -1;
        }
    }

    unsigned long **hashTable2 = malloc(setSize2 * sizeof(unsigned long *));

    for (long i = 0; i < setSize2; i++)
    {
        hashTable2[i] = malloc(assocNum2 * sizeof(unsigned long));
    }
    for (long i = 0; i < setSize2; i++)
    {
        for (long j = 0; j < assocNum2; j++)
        {
            hashTable2[i][j] = '\0';
        }
    }

    long **FIFOTable2 = malloc(setSize2 * sizeof(long *));

    for (long i = 0; i < setSize2; i++)
    {
        FIFOTable2[i] = malloc(assocNum2 * sizeof(unsigned long));
    }

    for (long i = 0; i < setSize2; i++)

    {
        for(long j = 0; j <assocNum2; j++){
        FIFOTable2[i][j] = -1;
        }
    }


    long **lruTable2 = malloc(setSize2 * sizeof(long *));

    for (long i = 0; i < setSize2; i++)
    {
        lruTable2[i] = malloc(assocNum2 * sizeof(long));
    }

    for (long i = 0; i < setSize2; i++)
    {
        for (long j = 0; j < assocNum2; j++)
        {
            lruTable2[i][j] = -1;
        }
    }

    FILE *fp = fopen(argv[8], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    long memread = 0;
    long memwrite = 0;
    long cachehit1 = 0;
    long cachemiss1 = 0;
    long cachehit2 = 0;
    long cachemiss2 = 0;

    char op;
    unsigned long bits;

    long time = 0;
    long thInsert = 0;

    while (fscanf(fp, "%c %lx", &op, &bits) == 2)
    {

        cacheSearch(hashTable1, cacheSize1, setSize1, assocNum1, blockSize1, cachePol1, &memread, &memwrite, &cachehit1, &cachemiss1, op, bits, &time, FIFOTable1, lruTable1,
                    hashTable2, cacheSize2, setSize2, assocNum2, cachePol2, FIFOTable2, lruTable2, &cachehit2, &cachemiss2,&thInsert);
        fscanf(fp, "%*[^\n]");
        fgetc(fp);
    }

    /*while (fscanf(fp, "%c %lx", &op, &bits) == 2)
    {
        cacheSearch(hashTable1, cacheSize1, setSize1, assocNum1, blockSize1, cachePol1, &memread, &memwrite, &cachehit1, &cachemiss1, op, bits, &time, FIFOTable1, lruTable1,
                    hashTable2, cacheSize2, setSize2, assocNum2, cachePol2, FIFOTable2, lruTable2, &cachehit2, &cachemiss2);
        fscanf(fp, "%*[^\n]");
        fgetc(fp);
    }
    */

    printf("memread:%ld\n", memread);
    printf("memwrite:%ld\n", memwrite);
    printf("l1cachehit:%ld\n", cachehit1);
    printf("l1cachemiss:%ld\n", cachemiss1);
    printf("l2cachehit:%ld\n", cachehit2);
    printf("l2cachemiss:%ld\n", cachemiss2);

    fclose(fp);

    for (long i = 0; i < setSize1; i++)
    {
        free(hashTable1[i]);
    }
    free(hashTable1);

    for (long i = 0; i < setSize1; i++)
    {
        free(lruTable1[i]);
    }
    free(lruTable1);

            for (long i = 0; i < setSize1; i++)
    {
        free(FIFOTable1[i]);
    }


    free(FIFOTable1);

    for (long i = 0; i < setSize2; i++)
    {
        free(hashTable2[i]);
    }
    free(hashTable2);

    for (long i = 0; i < setSize2; i++)
    {
        free(lruTable2[i]);
    }
    free(lruTable2);

        for (long i = 0; i < setSize2; i++)
    {
        free(FIFOTable2[i]);
    }

    free(FIFOTable2);

    return EXIT_SUCCESS;
}
