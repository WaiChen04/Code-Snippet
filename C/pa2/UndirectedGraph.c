#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name[80];
    struct Node *next;
};
typedef struct Node Node;

Node *createNode(char name[], Node *next)
{
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = next;
    return newNode;
}

void INSERT(Node **head, char insert[])
{
    Node *prev = NULL;
    Node *ptr = *head;

    while (ptr)
    {
        if (strcmp(ptr->name, insert) == 0)
        {
            return;
        }
        else if (strcmp(ptr->name, insert) > 0)
        {
            break;
        }
        else
        {

            prev = ptr;
            ptr = ptr->next;
        }
    }

    Node *newNode = createNode(insert, ptr);
    if (prev == NULL)
    {

        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        prev->next = newNode;
    }
}


void addEdge(Node *adjList[], int length, char target[], char edge[])
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, target) == 0)
        {
            INSERT(&adjList[i]->next, edge);
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, edge) == 0)
        {
            INSERT(&adjList[i]->next, target);
        }
    }
}

void freeAdjList(Node *adjList[], int length)
{
    for (int i = 0; i < length; i++)
    {
        Node *ptr = adjList[i];
        while (ptr)
        {
            Node *prev = ptr;
            ptr = ptr->next;
            free(prev);
        }
    }
}

void printCount(Node *adjList[], int length, char target[])
{
    int count = -1;
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, target) == 0)
        {
            Node *ptr = adjList[i];
            while (ptr)
            {
                count++;
                ptr = ptr->next;
            }
        }
    }

    printf("%d\n", count);
}

void printList(Node *adjList[], int length, char target[])
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, target) == 0)
        {
            Node *ptr = adjList[i]->next;
            while (ptr)
            {
                printf("%s ", ptr->name);
                ptr = ptr->next;
            }
            printf("\n");
        }
    }
}

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    int nVert;
    fscanf(fp, "%d\n", &nVert);

Node **adjList = malloc(nVert * sizeof(Node *));
    for (int i = 0; i < nVert; i++)
    {
        char name[80];
        fscanf(fp, "%s\n", name);
        adjList[i] = createNode(name, NULL);
    }

    char target[80];
    char edge[80];

    while (fscanf(fp, "%s %s\n", target, edge) == 2)
    {
        addEdge(adjList, nVert, target, edge);
    }

    fclose(fp);

    FILE *fp2 = fopen(argv[2], "r");
    if (fp2 == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    char op[80];
    char target2[80];

    while (fscanf(fp2, "%s %s\n", op, target2) == 2)
    {
        if (strcmp(op, "d") == 0)
        {
            printCount(adjList, nVert, target2);
        }
        if (strcmp(op, "a") == 0)
        {
            printList(adjList, nVert, target2);
        }
    }

    fclose(fp2);

    freeAdjList(adjList, nVert);
        free(adjList);


    return EXIT_SUCCESS;
}
