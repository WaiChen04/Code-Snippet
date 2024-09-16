#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int num;
    struct Node *next;
};
typedef struct Node Node;

Node *create(int num, Node *next)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = next;
    return newNode;
}

Node *DELETE(Node *head, int key)
{

    Node *prev = NULL;
    Node *ptr = head;

    if (head != NULL && head->num == key)
    { /*deletes head*/
        head = head->next;
        free(ptr);
        return head;
    }

    while (ptr)
    { /*Traverse*/
        if (ptr->num == key)
            break;
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
    { /*Doesn't delete anything*/
        return head;
    }
    else
    {
        prev->next = ptr->next; /*Deletes something*/
        free(ptr);

        return head;
    }
}

void printList(Node *head)
{
    if (head == NULL)
    {
        printf("EMPTY\n");
        return;
    }
    Node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->num);
        ptr = ptr->next;
    }
    printf("\n");
}

void freeLinkedList(Node *head)
{
    Node *prev = NULL;
    while (head)
    {
        prev = head;
        head = head->next;
        free(prev);
    }
}

void INSERT(Node **head, int num)
{
    Node *prev = NULL;
    Node *ptr = *head;

    while (ptr)
    {
        if (ptr->num == num)
        { /*insert nothing cuz dup*/
            return;
        }
        else if (ptr->num > num)
        { /*to insert in sorted order*/
            break;
        }
        else
        {

            prev = ptr;
            ptr = ptr->next;
        }
    }

    Node *newNode = create(num, ptr);
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

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    Node *head = NULL;
    int addnum;
    char op[100];

    while (fscanf(fp, "%s %d\n", op, &addnum) == 2)
    {

        if (strcmp(op, "INSERT") == 0)
        {
            INSERT(&head, addnum);
        }
        else if (strcmp(op, "DELETE") == 0)
        {
            head = DELETE(head, addnum);
        }
        printList(head);
    }

    fclose(fp);
    freeLinkedList(head);
    return EXIT_SUCCESS;
}
