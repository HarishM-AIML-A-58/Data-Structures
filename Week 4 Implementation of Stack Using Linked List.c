#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node* next;
};

struct node* top = NULL;

void push(int ele) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        newnode->next = top;
        top = newnode;
    }
}

int pop() {
    if (top == NULL) {
        printf("\nStack Underflow\n");
        return -1;
    } else {
        int popped = top->data;
        struct node* temp = top;
        top = top->next;
        free(temp);
        return popped;
    }
}

int peek() {
    if (top != NULL) {
        return top->data;
    } else {
        printf("\nStack is empty\n");
        return -1;
    }
}

int isEmpty() {
    return top == NULL;
}

void display() {
    struct node* t = top;
    while (t != NULL) {
        printf("%d\t", t->data);
        t = t->next;
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);
    display();

    printf("Top element is %d\n", peek());

    printf("Popped element is %d\n", pop());
    display();

    printf("Popped element is %d\n", pop());
    display();

    printf("Is stack empty? %s\n", isEmpty() ? "Yes" : "No");

    printf("Popped element is %d\n", pop());
    display();

    printf("Is stack empty? %s\n", isEmpty() ? "Yes" : "No");

    return 0;
}
