#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int isEmpty() {
    return top == NULL;
}

int evaluatePostfix(char* expression) {
    int i = 0;
    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            push(expression[i] - '0');
        } else {
            int val1 = pop();
            int val2 = pop();
            switch (expression[i]) {
                case '+': push(val2 + val1); break;
                case '-': push(val2 - val1); break;
                case '*': push(val2 * val1); break;
                case '/': push(val2 / val1); break;
            }
        }
        i++;
    }
    return pop();
}

int main() {
    char postfix[100] = "53+62/*35*+";
    printf("Postfix expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}
