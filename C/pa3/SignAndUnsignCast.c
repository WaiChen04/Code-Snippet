#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int num;
    struct Node *next;
};
typedef struct Node Node;

Node *createNode(int num, Node *next) {
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = next;
    return newNode;
}

void push(Node **stack, int num) {
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

void theConvertor(int num, int bits, char src, char dest) {

    if(src == 'u' && dest == 's'){
        int max = (1 << (bits- 1)) - 1;
        int change = (1 << (bits));
        if(num <= max){
            printf("%d", num);
            return;
        }else{
            printf("%d", (num - change));
            return;
        }



    }

    if(src == 's' && dest == 'u'){
        int change = (1 << (bits));
        if(num >= 0){
            printf("%d", num);
            return;
        }else{
            printf("%d", (num + change));
            return;
        }

        

    }




}

int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    int num;
    int bits;
    char src;
    char dest;


    while (fscanf(fp, "%d %d %c %c", &num, &bits, &src, &dest) == 4) {
        theConvertor(num, bits, src, dest);
        printf("\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
