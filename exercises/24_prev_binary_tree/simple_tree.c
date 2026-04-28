#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->tree_node = tree_node;
    new_node->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

TreeNode* dequeue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }
    
    QueueNode *temp = q->front;
    TreeNode *tree_node = temp->tree_node;
    
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (size == 0 || level_order[0] == INT_MIN) {
        return NULL;
    }
    
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;
    
    Queue *q = create_queue();
    enqueue(q, root);
    
    int i = 1;
    while (!is_empty(q) && i < size) {
        TreeNode *current = dequeue(q);
        
        if (i < size && level_order[i] != INT_MIN) {
            current->left = (TreeNode*)malloc(sizeof(TreeNode));
            current->left->val = level_order[i];
            current->left->left = NULL;
            current->left->right = NULL;
            enqueue(q, current->left);
        }
        i++;
        
        if (i < size && level_order[i] != INT_MIN) {
            current->right = (TreeNode*)malloc(sizeof(TreeNode));
            current->right->val = level_order[i];
            current->right->left = NULL;
            current->right->right = NULL;
            enqueue(q, current->right);
        }
        i++;
    }
    
    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    
    TreeNode *stack[100];
    int top = -1;
    
    stack[++top] = root;
    
    while (top >= 0) {
        TreeNode *current = stack[top--];
        printf("%d ", current->val);
        
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}