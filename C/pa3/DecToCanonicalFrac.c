#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertToCon(double num, int bits) {

    int exp = 0;
    int count = 0;

    double max = 1.0;
    double orginalnum = num;
    double maxNum = 0;

    while (num >= max){
        max = max *2;
        exp++;
        
    }
    max = max/2;
    exp--;

while(num == orginalnum){
    double firstresult = num -max;
        if(firstresult >= 0){
            num = firstresult;
            printf("1");
            maxNum = maxNum + max;
            max = max/2;

            
        }else{
            max = max/2;
            exp--;
        }
}
        printf(".");

    while(num != 0){
        double result = num -max;
        if(result >= 0){
            num = result;
            printf("1");
            maxNum = maxNum + max;
            max = max/2;
            
        }else{
            printf("0");
            max = max/2;
        }
        count++;

        if(count == bits){
            printf(" %d", exp);
            return;
        }
    }


for(int  i = count; i < bits;i++){
    printf("0");
}
            printf(" %d", exp);






}

int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    double num;
    int bits;

    while (fscanf(fp, "%lf %d", &num, &bits) == 2) {
        convertToCon(num, bits);
        printf("\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
