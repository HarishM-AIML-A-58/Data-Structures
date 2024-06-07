#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* head = NULL;
struct node* tail = NULL;

void enqueue(int ele) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        newnode->next = NULL;
        if (tail == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }
}

int dequeue() {
    if (head == NULL) {
        printf("\nQueue Underflow\n");
        return -1;
    } else {
        int dequeued = head->data;
        struct node* temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        free(temp);
        return dequeued;
    }
}

int isEmpty() {
    return head == NULL;
}

void display() {
    struct node* t = head;
    while (t != NULL) {
        printf("%d\t", t->data);
        t = t->next;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    printf("Dequeued element: %d\n", dequeue());
    display();

    printf("Dequeued element: %d\n", dequeue());
    display();

    printf("Is queue empty? %s\n", isEmpty() ? "Yes" : "No");

    enqueue(40);
    display();

    printf("Is queue empty? %s\n", isEmpty() ? "Yes" : "No");

    return 0;
}
