#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;
struct node* newnode;

void insert(int ele) {
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = ele;
    newnode->left = newnode->right = NULL;
    
    if (root == NULL) {
        root = newnode;
    } else {
        struct node* current = root;
        struct node* parent = NULL;
        
        while (1) {
            parent = current;
            if (ele < parent->data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newnode;
                    return;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newnode;
                    return;
                }
            }
        }
    }
}

void inorder(struct node* t) {
    if (root == NULL) return;
    if (t != NULL) {
        inorder(t->left);
        printf("%d ", t->data);
        inorder(t->right);
    }
}

void preorder(struct node* t) {
    if (root == NULL) return;
    if (t != NULL) {
        printf("%d ", t->data);
        preorder(t->left);
        preorder(t->right);
    }
}

void postorder(struct node* t) {
    if (root == NULL) return;
    if (t != NULL) {
        postorder(t->left);
        postorder(t->right);
        printf("%d ", t->data);
    }
}

int main() {
    insert(5);
    insert(3);
    insert(7);
    insert(2);
    insert(4);
    insert(6);
    insert(8);
    
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
