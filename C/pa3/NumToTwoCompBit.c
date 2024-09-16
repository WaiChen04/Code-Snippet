#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    long num;
    struct Node *next;
};
typedef struct Node Node;

Node *createNode(long num, Node *next) {
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = next;
    return newNode;
}

void push(Node **stack, long num) {
    Node *newNode = createNode(num, *stack);
    *stack = newNode;
}

void pop(Node **stack) {
    if (*stack != NULL) {
        Node *temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}

void convertToTwoComp(long num, long bits) {
    long max =1;
    long min = -1;
    int count = 1;

    for(int i = 1; i < bits; i++){
            max = max *2;
        }
    max--;
    for(int i = 1; i < bits; i++){
            min = min *2;
        }

    if(num <= min){
        printf("1");
        for(int i = 1; i < bits; i++){
            printf("0");
        }
        return;
    }

    if(num >= max){
        printf("0");
        for(int i = 1; i < bits; i++){
            printf("1");
        }
        return;
    }



    min = min *-1;

if(num <0){
    num = num + min;
    min = min >> 1;
    printf("1");
    while(num != 0){
        long result = num - min;
        if(result == 0){
            printf("1");
            num = result;
            count++;
        }
        if(result < 0){
            printf("0");
            min = min >> 1;
                    count++;
        }
        if(result > 0){
            printf("1");
            num = result;
            min = min >> 1;
                    count++;
        }


    }
} else{
    min = min >> 1;
    printf("0");
    while(num != 0){
        long result = num - min;

        if(result == 0){
            printf("1");
            num = result;
            count++;
        }
        if(result < 0){
            printf("0");
            min = min >> 1;
            count++;
        }
        if(result > 0){
            printf("1");
            num = result;
            min = min >> 1;
            count++;
        }



    }
}


    if(count == bits){
        return;
    }
    while(count < bits){
    printf("0");
    count++;

    }

}

int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    long num;
    long bits;

    while (fscanf(fp, "%ld %ld", &num, &bits) == 2) {
        convertToTwoComp(num, bits);
        printf("\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
