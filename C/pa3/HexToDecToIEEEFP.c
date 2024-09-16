#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addArray(int *array, int totalBits, int bit)
{
    for (int i = 0; i < totalBits; i++)
    {
        if (array[i] == 2)
        {
            array[i] = bit;
            return;
        }
    }
}

int* hexiToBinary(int totalBits, char* hexi){

    int *array = malloc(totalBits * sizeof(int));

    for (int i = 0; i < totalBits; i++)
    {
        array[i] = 2;
    }

    

    int i = 2;

    while(hexi[i] != '\0'){
        if(hexi[i] == '0'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == '1'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == '2'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
              addArray(array,totalBits,1);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == '3'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == '4'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == '5'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == '6'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == '7'){
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == '8'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == '9'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == 'a'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == 'b'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == 'c'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == 'd'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
            addArray(array,totalBits,1);
        }
        if(hexi[i] == 'e'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,0);
        }
        if(hexi[i] == 'f'){
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
            addArray(array,totalBits,1);
        }

        i++;
    }

    return array; 

}


void convertStuff(int totalBits, int expBits, int fracBits, char* hexi, int numOfDeci, int lengthOfPat){

            int *array = hexiToBinary(lengthOfPat *4, hexi);
            double num = 0.0;

            int bias = ((1 << (expBits - 1)) - 1);

            int exp = 0;

            int isNotSub = 0;

            int k = 1;



            for(int i = 1 + (lengthOfPat*4) - totalBits; i < expBits + 1  + (lengthOfPat*4) - totalBits; i++){

                exp = exp + (array[i]*(1 << (expBits - 1 - (k-1))));
                k++;
                if( array[i] == 1){
                    isNotSub = 1;
                }
            }

            exp = exp -bias;

            double startingPower = 1;

            if(exp !=0){
                if(exp > 0){
                    for(int i = 0; i < exp; i++){
                        startingPower = startingPower *2;
                    }
                }

                if(exp < 0){
                    exp = exp *-1;
                    for(int i = 0; i < exp; i++){
                        startingPower = startingPower /2;
                    }
                }
            }

            if(isNotSub == 1){
                num = num + startingPower;
                startingPower = startingPower /2;

            }

            for(int i = expBits + 1  + (lengthOfPat*4) - totalBits; i < (lengthOfPat*4); i++){               
                num = num + (array[i]* startingPower);
                startingPower = startingPower /2;
            }

            if(array[(lengthOfPat*4) - totalBits] == 1){
                num = num*-1;
            }



    char printString[80];
    sprintf(printString, "%%.%df", numOfDeci);

            printf(printString, num);

            free(array);

}


int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    int totalBits;
    int expBits;
    int fracBits;
    char hexi[80];
    int numOfDeci;

    while (fscanf(fp, "%d %d %d %s %d", &totalBits, &expBits, &fracBits, hexi, &numOfDeci) == 5)
    {
        int lengthOfPat = 0;
        int i = 2;
        while(hexi[i] != '\0'){
            lengthOfPat++;
            i++;
        }

        convertStuff(totalBits, expBits, fracBits, hexi, numOfDeci, lengthOfPat);
            printf("\n");
    }
       


    fclose(fp);

    return EXIT_SUCCESS;
}
