#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int num;
    struct Node *right;
    struct Node *left;
};
typedef struct Node Node;

Node *create(int num, Node *left, Node *right)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}
void insert(Node **root, int num, int count)
{
    Node *ptr = *root;
    if (ptr == NULL)
    {
        Node *addNode = create(num, NULL, NULL);
        *root = addNode;
        printf("inserted %d\n", count);
    }
    else
    {
        int addNodeNum = num;
        int ptrNum = ptr->num;
        if (addNodeNum == ptrNum)
        {
            printf("duplicate\n");
            return;
        }
        if (addNodeNum < ptrNum)
        {
            if (ptr->left == NULL)
            {
                Node *addNode = create(num, NULL, NULL);
                ptr->left = addNode;
                printf("inserted %d\n", count + 1);
            }
            else
            {
                insert(&(ptr->left), num, count + 1);
            }
        }
        else if (addNodeNum > ptrNum)
        {
            if (ptr->right == NULL)
            {
                Node *addNode = create(num, NULL, NULL);
                ptr->right = addNode;
                printf("inserted %d\n", count + 1);
            }
            else
            {
                insert(&(ptr->right), num, count + 1);
            }
        }
    }
}

void find(Node *root, int num)
{
    int count = 1;
    Node *ptr = root;
    while (ptr != NULL)
    {
        if (num == ptr->num)
        {
            printf("present %d\n", count);
            return;
        }
        else if (num < ptr->num)
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
        count++;
    }
    printf("absent\n");
}

void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    Node *root = NULL;
    int addnum;
    char op[100];

    while (fscanf(fp, "%s %d\n", op, &addnum) == 2)
    {

        if (strcmp(op, "i") == 0)
        {
            insert(&root, addnum, 1);
        }
        else if (strcmp(op, "s") == 0)
        {
            find(root, addnum);
        }
    }

    fclose(fp);
    freeTree(root);

    return EXIT_SUCCESS;
}