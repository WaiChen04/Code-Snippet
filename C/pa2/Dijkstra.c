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

void swap(Node *PQ[], int index1, int index2)
{
    Node *temp = PQ[index1];
    PQ[index1] = PQ[index2];
    PQ[index2] = temp;
}

void swim(Node *PQ[], int k)
{
    while (k > 1 && (PQ[k / 2]->weight > PQ[k]->weight))
    {
        swap(PQ, k, k / 2);
        k = k / 2;
    }
}

void sink(Node *PQ[], int k, int *PQsize)
{

    while (2 * k <= *PQsize)
    {
        int j = 2 * k;
        if (j < *PQsize && (PQ[j]->weight > PQ[j + 1]->weight))
        {
            j++;
        }
        if (!(PQ[k]->weight > PQ[j]->weight))
        {
            break;
        }
        swap(PQ, k, j);

        k = j;
    }
}

void addPQ(Node *PQ[], Node *v, int weight, int *PQsize)
{
    (*PQsize)++;
    PQ[*PQsize] = createNode(v->name, NULL, weight);
    swim(PQ, *PQsize);
}

void modPQ(Node *PQ[], Node *v, int newWeight, int *PQsize)
{
    int boo = 0;
    for (int i = 1; i <= *PQsize; i++)
    {
        if (strcmp(v->name, PQ[i]->name) == 0)
        {
            PQ[i]->weight = newWeight;
            boo = 1;
            swim(PQ, i);

        }
    }
    if(boo == 0){
        addPQ(PQ,v, newWeight,PQsize);
    }
}


char* minPQ(Node *PQ[], int *PQsize)
{
    char* returnName = malloc(80*sizeof(char*));
    strcpy(returnName, PQ[1]->name);
    (*PQsize)--;
    swap(PQ, 1, *PQsize);
    sink(PQ, 1, PQsize);
    free(PQ[*PQsize + 1]);
    return returnName;
}


int weightfind(Node *adjList[], int srcIndex, char vName[])
{

    int weight;
    Node *ptr = adjList[srcIndex];
    while (ptr)
    {
        if (strcmp(ptr->name, vName) == 0)
        {
            weight = ptr->weight;
        }
        ptr = ptr->next;
    }
    free(ptr);

    return weight;
}

void Dijkstra(Node *adjList[], int length, char target[], int distance[])
{

    Node *Q[10000];
    Q[0] = NULL;
    int PQsize = 0;


    for (int i = 0; i < length; i++)
    {
        if (strcmp(target, adjList[i]->name) == 0)
        {
            distance[i] = 0;
            
        }      

    }

    for (int i = 0; i < length; i++)
    {
        if (strcmp(target, adjList[i]->name) == 0)
        {
        
            
        }else{
            distance[i] = INT_MAX;
            
        }

        addPQ(Q,adjList[i], distance[i], &PQsize);      
        
        
    }

    while (PQsize != 0)
    {

        char* uName = minPQ(Q, &PQsize);
        int uIndex;

        Node *u;

        Node *v;
        int vIndex;
        
        for(int i = 0; i <length; i++){
            if(strcmp(uName, adjList[i]->name) == 0){
                u = adjList[i];
                v = adjList[i];
                uIndex = i;
            }
        }

        v = u;

        while (v)
        {

            for (int k = 0; k < length; k++)
            {
                if (strcmp(v->name, adjList[k]->name) == 0)
                {
                    vIndex = k;
                }
            }
            if(distance[uIndex]!= INT_MAX){

                int alt = distance[uIndex] + weightfind(adjList, uIndex, v->name);
                if (alt < distance[vIndex])
                {
                    distance[vIndex] = alt;
                    modPQ(Q, v, alt, &PQsize);
                    for (int i = 0; i < length; i++)
                   {addPQ(Q,adjList[i], distance[i], &PQsize);    

                   }
                    
                }
            }
            v = v->next;
        }
        free(v);
        free(uName);
        
    }

    free(Q[0]);
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

    while (fscanf(fp2, "%s\n", target2) == 1)
    {
    int *distance = malloc(nVert * sizeof(int));
        for (int i = 0; i < nVert; i++)
        {
            distance[i] = 0;
        }
        Dijkstra(adjList, nVert, target2, distance);
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
