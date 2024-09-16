#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addArray(int *array, int fracBits, int bit)
{
    for (int i = 0; i < fracBits; i++)
    {
        if (array[i] == 2)
        {
            array[i] = bit;
            return;
        }
    }
}

void SignBit(double num)
{
    if (num < 0)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
}

void printExp(int expNum, int expBits)
{
    int bias = ((1 << (expBits - 1)) - 1);
    int numGoal = bias + expNum;
    int count = 0;

    int max = 1 << (expBits - 1);

    while (numGoal != 0)
    {
        long result = numGoal - max;
        if (result == 0)
        {
            printf("1");
            numGoal = result;
        }
        if (result < 0)
        {
            printf("0");
            max = max >> 1;
        }
        if (result > 0)
        {
            printf("1");
            numGoal = result;
            max = max >> 1;
        }
        count++;
    }

    for (int i = count; i < expBits; i++)
    {
        printf("0");
    }
}

void addOnetoArray(int *array, int fracBits)
{

    for(int i = fracBits -1; i >= 0; i--){
        if(array[i] == 0){
            array[i] = 1;
            break;
        }
        if(array[i] == 1){
            array[i] = 0;
        }
    }
    
}


void subtractOnetoArray(int *array, int fracBits)
{

    for(int i = fracBits -1; i >= 0; i--){
        if(array[i] == 0){
            array[i] = 1;
            break;
        }
        if(array[i] == 1){
            array[i] = 0;
        }
    }
    
}

void convertToCon(double num, int expBits, int fracBits)
{

    if(num <0){
        num = num *-1;
    }


    int exp = 0;
    int count = 0;

    int needNotcarry = 0;


    double max = 1.0;
    double orginalnum = num;
    double maxNum = 0;



    int *fracArray = malloc(fracBits * sizeof(int));

    for (int i = 0; i < fracBits; i++)
    {
        fracArray[i] = 2;
    }

    while (num >= max)
    {
        max = max * 2;
        exp++;
    }
    max = max / 2;
    exp--;

    while (num == orginalnum)
    {
        double firstresult = num - max;
        if (firstresult >= 0)
        {
            num = firstresult;
            maxNum = maxNum + max;
            max = max / 2;
        }
        else
        {
            max = max / 2;
            exp--;
        }
        if (exp == -((1 << (expBits - 1)) - 1))
        {
            break;
        }
    }

    while (num != 0)
    {
        double result = num - max;
        if (result >= 0)
        {
            num = result;
            addArray(fracArray, fracBits, 1);
            maxNum = maxNum + max;
            max = max / 2;
        }
        else
        {
            addArray(fracArray, fracBits, 0);
            max = max / 2;
            needNotcarry = 1;
        }
        count++;

        if (count == fracBits)
        {
            break;
        }
    }

    for (int i = count; i < fracBits; i++)
    {
        addArray(fracArray, fracBits, 0);
        needNotcarry = 1;
    }

    double checkRoundUp = num - max;
    if (checkRoundUp >= 0)
    {
        int isNotTied = 0;
        num = checkRoundUp;
        max = max / 2;
        while (num != 0)
        {
            double result = num - max;
            if (result >= 0)
            {
                isNotTied = 1;
                if (needNotcarry == 0)
                {

                    for (int i = 0; i < fracBits; i++)
                    {
                        fracArray[i] = 0;
                    }
                    exp++;
                }
                else
                {
                    addOnetoArray(fracArray, fracBits);
                }
                break;
            }
        }
        if (isNotTied == 0)
        {
            if(fracArray[fracBits-1] == 1){
                if (needNotcarry == 0)
                {

                    for (int i = 0; i < fracBits; i++)
                    {
                        fracArray[i] = 0;
                    }
                    exp++;
                }
                else
                {
                    addOnetoArray(fracArray, fracBits);
                }

            }

        }
    }

    printExp(exp, expBits);

    for (int i = 0; i < fracBits; i++)
    {

        printf("%d", fracArray[i]);
    }
    free(fracArray);
}

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    double num;
    int totalBits;
    int expBits;
    int fracBits;

    while (fscanf(fp, "%lf %d %d %d", &num, &totalBits, &expBits, &fracBits) == 4)
    {
        SignBit(num);
        convertToCon(num, expBits, fracBits);
        printf("\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
