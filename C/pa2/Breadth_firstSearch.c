#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name[80];
    struct Node *next;
};
typedef struct Node Node;

struct QNode
{

    struct Node *last;
    struct Node *first;
};
typedef struct QNode QNode;

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

void enqueue(QNode *queue, char name[])
{
    Node *oldLast = queue->last;
    queue->last = createNode(name, NULL);
    if (queue->first == NULL)
    {
        queue->first = queue->last;
    }
    else
    {
        oldLast->next = queue->last;
    }
}

void dequeue(QNode *queue)
{
    queue->first = queue->first->next;

    if (queue->first == NULL)
    {
        queue->last = NULL;
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

void BFS(Node *adjList[], int length, char target[])
{
    QNode *newQ = malloc(sizeof(QNode));
    newQ->first = NULL;
    newQ->last = NULL;

    char **visited = malloc(length * sizeof(char *));
    for (int i = 0; i < length; i++)
    {
        visited[i] = malloc(80 * sizeof(char));
        visited[i][0] = '\0';
    }

    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, target) == 0)
        {
            enqueue(newQ, adjList[i]->name);
            strcpy(visited[0], adjList[i]->name);
        }
    }

    while (newQ->first != NULL)
    {
        Node *current = newQ->first;
        printf("%s ", current->name);
        dequeue(newQ);
        Node *ptr = NULL;

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
            if (checkVisited(visited, length, ptr->name) == 0)
            {
                addVisited(visited, length, ptr->name);
                enqueue(newQ, ptr->name);
                
            }
            ptr = ptr->next;
        }
        free(ptr);
        free(current);
    }

    for (int i = 0; i < length; i++)
    {
        free(visited[i]);
    }
    free(visited);

    free(newQ);
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

    char target2[80];

    if(fscanf(fp2, "%s\n", target2) == 1){
        BFS(adjList,nVert, target2);
    }

    while (fscanf(fp2, "%s\n", target2) == 1)
    {
        printf("\n");
        BFS(adjList, nVert, target2);

    }

    fclose(fp2);

    freeAdjList(adjList, nVert);
    free(adjList);

    return EXIT_SUCCESS;
}
