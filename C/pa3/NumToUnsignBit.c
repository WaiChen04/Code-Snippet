#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    long num;
    long bits;

    while (fscanf(fp, "%ld %ld", &num, &bits) == 2) {
        convertToUnsigBit(num, bits);
        printf("\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
