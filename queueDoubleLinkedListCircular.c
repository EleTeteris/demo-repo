#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {   
    int data;
    struct node *prev;
    struct node *next;    
} node;

node* createNewNode(int value) {
    node *newNode = NULL;
    newNode = (node*) malloc(sizeof(node));
    newNode -> prev = NULL;
    newNode -> next = NULL;
    newNode -> data = value;
    if(!newNode) {
        printf("Error allocating memory.Exiting program...\n");
        exit(1);
    }
    return newNode;
}

void createQueue(node **head, node **tail) {
    unsigned short int size;
    node *newNode = NULL;
    do {
        printf("Type the size of the queue: ");
        scanf("%u", &size);
    }while(size <= 0);

    for(int i = 0; i < size; i++) {
        if(((*head) == (*tail)) && ((*head) == NULL && (*tail) == NULL)) {
            (*head) = createNewNode(i + 1);
            (*head) -> next = (*head);
            (*head) -> prev = (*head);
            (*tail) = (*head);
            (*tail) -> next = (*tail);
            (*tail) -> prev = (*tail);
        }
        else if((*head) == (*tail)) {
            (*head) -> next = createNewNode(i + 1);
            (*tail) = (*head) -> next;
            (*tail) -> next = (*head);
            (*tail) -> prev = (*head);
            (*head) -> prev = (*tail);
        }
        else {
            newNode = createNewNode(i + 1);
            newNode -> prev = (*tail);
            (*tail) -> next = newNode;
            newNode -> next = (*head);
            (*head) -> prev = newNode;
            (*tail) = newNode;
        }
    } 
}

void enqueue(node **head, node **tail) {
    int val;
    printf("Type a value: ");
    scanf("%d", &val);
    node *newNode = createNewNode(val);
    if(((*head) == (*tail)) && ((*head) == NULL && (*tail) == NULL)) {
        (*head) = newNode;
        (*head) -> next = (*head);
        (*head) -> prev = (*head);
        (*tail) = (*head);
        (*tail) -> next = (*tail);
        (*tail) -> prev = (*tail);
    }
    else if((*head) == (*tail)) {
        (*head) -> next = newNode;
        (*tail) = (*head) -> next;
        (*tail) -> next = (*head);
        (*tail) -> prev = (*head);
        (*head) -> prev = (*tail);
    }
    else {
        newNode -> prev = (*tail);
        (*tail) -> next = newNode;
        newNode -> next = (*head);
        (*head) -> prev = newNode;
        (*tail) = newNode;
    }
}

bool isEmpty(node *head, node *tail) {
    return (head == NULL) || (tail == NULL);
}

void dequeue(node **head, struct node **tail) {
    if(isEmpty((*head), (*tail))) {
        printf("The queue is already empty, cannot remove anymore items.\n");
        return;
    }
    else if((*head) == (*tail)) {
        free(*head);
        (*head) = (*tail) = NULL;
    }
    else {
        node *temp = (*head);
        (*head) = temp -> next;
        (*head) -> prev = (*tail);
        (*tail) -> next = (*head);
        free(temp);
    }    
}

void printQueue(node *head, struct node *tail) {
    node *temp = head;
    while(temp != tail) {
        printf("%d -> ", temp -> data);
        temp = temp -> next;
    }
    printf("%d\n", temp -> data);
}

int main() {
    node *head = NULL, *tail = NULL;

    createQueue(&head, &tail);
    printQueue(head, tail);
    dequeue(&head, &tail);
    enqueue(&head, &tail);
    printQueue(head, tail);
    
    return 0;
}