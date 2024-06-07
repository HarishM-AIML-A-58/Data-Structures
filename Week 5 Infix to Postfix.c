#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    char data;
    struct node* next;
};

struct node* top = NULL;

void push(char ele) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        newnode->next = top;
        top = newnode;
    }
}

char pop() {
    if (top == NULL) {
        printf("\nStack Underflow\n");
        return -1;
    } else {
        char popped = top->data;
        struct node* temp = top;
        top = top->next;
        free(temp);
        return popped;
    }
}

char peek() {
    if (top != NULL) {
        return top->data;
    } else {
        return -1;
    }
}

int isEmpty() {
    return top == NULL;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // Remove '(' from stack
        } else if (isOperator(infix[i])) {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }
    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main() {
    char infix[100] = "a+b*(c^d-e)^(f+g*h)-i";
    char postfix[100];

    printf("Infix expression: %s\n", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
