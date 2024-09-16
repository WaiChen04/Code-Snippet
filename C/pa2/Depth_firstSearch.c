#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name[80];
    struct Node *next;
    int weight;
};
typedef struct Node Node;


Node *createNode(char name[], Node *next, int weight)
{
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = next;
    newNode->weight = weight;
    return newNode;
}


void INSERT(Node **head, char insert[], int weight)
{
    Node *prev = NULL;
    Node *ptr = *head;

    while (ptr)
    {
        if (strcmp(ptr->name, insert) == 0)
        {
            return;
        }
        else if (strcmp(ptr->name, insert) < 0)
        { 
            break;
        }
        else
        {

            prev = ptr;
            ptr = ptr->next;
        }
    }

    Node *newNode = createNode(insert, ptr, weight);
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


void addEdge(Node *adjList[], int length, char target[], char edge[], int weight)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, target) == 0)
        {
            INSERT(&adjList[i]->next, edge, weight);
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


void push(Node **stack, char name[], int weight)
{
    Node *newNode = createNode(name, NULL, weight);
    newNode->next = *stack;
    *stack = newNode;
}

void pop(Node **stack)
{
    if (*stack != NULL)
    {
        *stack = (*stack)->next;
    }
}


void addVisited(char **visited, int length, char name[])
{
    for (int i = 0; i < length; i++)
    {
        if (*visited[i] =='\0')
        {
            strcpy(visited[i], name);
            return;
        }
        else if (strcmp(visited[i], name) == 0)
        {
            return;
        }
    }
}

int checkVisited(char **visited, int length, char name[])
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(visited[i], name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void printVisted(char **visited, int length){
        for (int i = 0; i < length; i++)
    {

        printf("%s ",visited[i]);


    }

}





void DFS(Node *adjList[], int length, char target[], int weight, char **visited)
{

    Node **newS = malloc(sizeof(Node *));
    *newS = createNode(target, NULL, weight);
    




    while (*newS != NULL)
    {
        Node *current = *newS;
        pop(newS);
        Node *ptr = NULL;

    if (checkVisited(visited, length, current->name) == 0){
        addVisited(visited, length,current->name);
        
        for (int i = 0; i < length; i++)
        {
            if (strcmp(adjList[i]->name, current->name) == 0)
            {
                ptr = adjList[i];
                break;
            }
        }

        while (ptr)
        {
            push(newS, ptr->name, ptr->weight);
            ptr = ptr->next;

        }
    }
        free(ptr);
        free(current);
    }

    free(newS);

}


void sortAdjList(Node *adjList[], int length)
{
    int i, j;
    Node *temp;
    for (i = 0; i < length - 1; i++)
    {
        for (j = i + 1; j < length; j++)
        {
            if (strcmp(adjList[i]->name, adjList[j]->name) > 0)
            {
                temp = adjList[i];
                adjList[i] = adjList[j];
                adjList[j] = temp;
            }
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
        adjList[i] = createNode(name, NULL, 0);
    }
    sortAdjList(adjList, nVert);

    char target[80];
    char edge[80];
    int weight;

    while (fscanf(fp, "%s %s %d\n", target, edge, &weight) == 3)
    {
        addEdge(adjList, nVert, target, edge, weight);
    }

    char **visited = malloc(nVert * sizeof(char *));
    for (int i = 0; i < nVert; i++)
    {
        visited[i] = malloc(80 * sizeof(char));
        visited[i][0] = '\0';
    }



for(int i = 0; i <nVert; i++){


    DFS(adjList, nVert, adjList[i]->name, adjList[i]->weight, visited);

}

printVisted(visited,nVert);

    fclose(fp);

    for (int i = 0; i < nVert; i++)
    {
        free(visited[i]);
    }
    free(visited);


    freeAdjList(adjList, nVert);
    free(adjList);

    return EXIT_SUCCESS;
}
