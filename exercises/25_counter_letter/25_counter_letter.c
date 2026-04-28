#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct TreeNode {
    char letter;
    int count;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* create_node(char letter) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->letter = tolower(letter);
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insert_or_update(TreeNode* root, char letter) {
    char lower_letter = tolower(letter);
    
    if (root == NULL) {
        return create_node(lower_letter);
    }
    
    if (lower_letter < root->letter) {
        root->left = insert_or_update(root->left, lower_letter);
    } else if (lower_letter > root->letter) {
        root->right = insert_or_update(root->right, lower_letter);
    } else {
        root->count++;
    }
    
    return root;
}

void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%c:%d\n", root->letter, root->count);
        inorder_traversal(root->right);
    }
}

void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[]) {
    const char* file_path = "paper.txt";
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    TreeNode* root = NULL;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            root = insert_or_update(root, c);
        }
    }
    
    fclose(file);
    
    inorder_traversal(root);
    
    free_tree(root);
    
    return 0;
}