#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node* next;
};

struct node* head = NULL;

void insertfront(int ele) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        newnode->next = head;
        head = newnode;
    }
}

void insertend(int ele) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        newnode->next = NULL;
        if (head == NULL) {
            head = newnode;
        } else {
            struct node* t = head;
            while (t->next != NULL) {
                t = t->next;
            }
            t->next = newnode;
        }
    }
}

int listsize() {
    int count = 0;
    struct node* t = head;
    while (t != NULL) {
        count++;
        t = t->next;
    }
    return count;
}

void insertpos(int ele, int pos) {
    int ls = listsize();
    if ((head == NULL && pos != 1) || pos <= 0 || pos > ls + 1) {
        printf("\nInvalid position to insert a node\n");
        return;
    }

    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->data = ele;
        if (pos == 1) {
            newnode->next = head;
            head = newnode;
        } else {
            struct node* temp = head;
            for (int count = 1; count < pos - 1; count++) {
                temp = temp->next;
            }
            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
}

void findnext(int s) {
    struct node* temp = head;
    while (temp != NULL && temp->data != s) {
        temp = temp->next;
    }
    if (temp != NULL && temp->next != NULL) {
        printf("\nNext element of %d is %d\n", s, temp->next->data);
    } else {
        printf("\nNo next element for %d\n", s);
    }
}

void findprev(int s) {
    if (head == NULL || head->data == s) {
        printf("\nNo previous element for %d\n", s);
        return;
    }
    struct node* temp = head;
    while (temp->next != NULL && temp->next->data != s) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        printf("\nPrevious element of %d is %d\n", s, temp->data);
    } else {
        printf("\nElement %d not found\n", s);
    }
}

void find(int s) {
    struct node* temp = head;
    while (temp != NULL && temp->data != s) {
        temp = temp->next;
    }
    if (temp != NULL) {
        printf("\nElement %d is present in the list\n", s);
    } else {
        printf("\nElement %d is not present in the list\n", s);
    }
}

void isempty() {
    if (head == NULL) {
        printf("\nList is empty\n");
    } else {
        printf("\nList is not empty\n");
    }
}

void deleteAtBeginning() {
    if (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
}

void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
    } else {
        struct node* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
}

void delete(int ele) {
    if (head == NULL) {
        printf("\nList is empty\n");
        return;
    }
    if (head->data == ele) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    } else {
        struct node* temp = head;
        while (temp->next != NULL && temp->next->data != ele) {
            temp = temp->next;
        }
        if (temp->next != NULL) {
            struct node* delNode = temp->next;
            temp->next = temp->next->next;
            free(delNode);
        } else {
            printf("\nElement %d not found\n", ele);
        }
    }
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
    insertfront(5);
    insertfront(10);
    insertfront(20);
    insertend(30);
    insertend(40);
    display();

    printf("\nAfter inserting 15 at the 2nd position\n");
    insertpos(15, 2);
    display();

    findnext(30);
    findprev(30);

    find(15);
    isempty();

    printf("\nAfter deleting the first element\n");
    deleteAtBeginning();
    display();

    printf("\nAfter deleting the last element\n");
    deleteAtEnd();
    display();

    printf("\nAfter deleting element 15\n");
    delete(15);
    display();

    return 0;
}
