#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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


void addVisited(char **visited, int length, char name[])
{
    for (int i = 0; i < length; i++)
    {
        if (*visited[i] == '\0')
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


void addMarks(Node *n, Node *adjList[], int marked[], int length, char **topSortArray, int *isCycle)
{

    int index;
    for (int i = 0; i < length; i++)
    {
        if (strcmp(adjList[i]->name, n->name) == 0)
        {
            index = i;
        }
    }

    if (marked[index] == 2)
    {
        return;
    }

    if (marked[index] == 1)
    { *isCycle = 1;
        return;
    }

    marked[index] = 1;

    Node *ptr = adjList[index];
    ptr = ptr->next;

    while (ptr)
    {
        addMarks(ptr, adjList, marked, length, topSortArray, isCycle);
        ptr = ptr->next;
    }

    marked[index] = 2;
    addVisited(topSortArray, length, n->name);
        free(ptr);
}

void topSort(Node *adjList[],char **topSortArray, int length, int *isCycle)
{

    
    for (int i = 0; i < length; i++)
    {
        topSortArray[i] = malloc(80 * sizeof(char));
        topSortArray[i][0] = '\0';
    }

    int *marked = malloc(length * sizeof(int));

    int bool = 0;
    for (int i = 0; i < length; i++)
    {
        marked[i] = 0;
    }
    while (bool == 0)
    {

        bool = 1;
        for (int i = 0; i < length; i++)
        {
            if (marked[i] == 0)
            {
                addMarks(adjList[i], adjList, marked, length, topSortArray, isCycle);
                
            }
            if (marked[i] == 1)
            {
                strcpy(topSortArray[0], "CYCLE");
            }
        }

        for (int i = 0; i < length; i++)
        {
            if (marked[i] == 0)
            {
                bool = 0;
            }
        }
    }
    free(marked);

}

int weightfind(Node *adjList[], int srcIndex, char vName[])
{

    int weight;
    Node *ptr = adjList[srcIndex];
    ptr = ptr->next;
    while (ptr)
    {
        if (strcmp(ptr->name, vName) == 0)
        {
            weight = ptr->weight;
        }
        ptr= ptr->next;
    }
    free(ptr);

    return weight;
}

void DAG_SSP(Node *adjList[], int length, char target[], int distance[])

{

    int isCycle =0;
    char **topSortArray = malloc(length * sizeof(char *));
    topSort(adjList, topSortArray, length, &isCycle);


    if (isCycle==1)
    {
    for (int i = 0; i < length; i++)
    {
        free(topSortArray[i]);
    }
    free(topSortArray);
        printf("CYCLE");
        return;
    }
    else
    {

        for (int i= 0; i < length; i++)
        {
            distance[i] = INT_MAX;
        }
        for (int i = 0; i < length; i++)
        {
            if (strcmp(target, adjList[i]->name) == 0)
            {
                distance[i] = 0;
            }
        }

        for (int i = 0; i < length; i++)
        {
            char uName[80];
            int uIndex;

            strcpy(uName, topSortArray[length-i-1]);

            Node *v;
            int vIndex;
            for (int j = 0; j < length; j++)
            {
                if (strcmp(uName, adjList[j]->name) == 0)
                {
                    v = adjList[j];
                    uIndex = j;
                }
            }
            v = v->next;
            char vName[80];
            while (v)
            {
                for (int k = 0; k < length; k++)
                {
                    if (strcmp(v->name, adjList[k]->name) == 0)
                    {
                        vIndex = k;
                    }

                    strcpy(vName, v->name);
                }
                int weight = weightfind(adjList, uIndex, vName);

                if (distance[uIndex] != INT_MAX &&distance[vIndex] > (distance[uIndex] + weight)){
                    distance[vIndex] = (distance[uIndex] + weight);
                }
            v = v->next;

            }
            free(v);
        }
    }
    for (int i = 0; i < length; i++)
    {
        free(topSortArray[i]);
    }
    free(topSortArray);

    for (int i = 0; i < length; i++)
        {
            printf("%s ", adjList[i]->name);
            if (distance[i] == INT_MAX)
            {
                printf("INF\n");
            }
            else
            {
                printf("%d\n", distance[i]);
            }
        }
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
    fclose(fp);



    FILE *fp2 = fopen(argv[2], "r");
    if (fp2 == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    char target2[80];
    printf("\n");

    while (fscanf(fp2, "%s\n", target2) == 1)
    {
    int *distance = malloc(nVert * sizeof(int));
    for (int i = 0; i < nVert; i++)
    {
        distance[i] = 0;
    }
        DAG_SSP(adjList, nVert, target2, distance);
        printf("\n");
                for (int i = 0; i < nVert; i++)
        {
            distance[i] = 0;
        }
        free(distance);
    }

        fclose(fp2);


    freeAdjList(adjList, nVert);
        free(adjList);

    return EXIT_SUCCESS;
}
