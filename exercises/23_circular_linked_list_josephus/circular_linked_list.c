#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) return NULL;

    Node* head = (Node*)malloc(sizeof(Node));
    head->id = 1;
    
    Node* current = head;
    for (int i = 2; i <= n; i++) {
        current->next = (Node*)malloc(sizeof(Node));
        current = current->next;
        current->id = i;
    }
    current->next = head;
    
    return head;
}

void free_list(Node* head) {
    if (!head) return;

    Node* current = head;
    Node* next_node;
    
    do {
        next_node = current->next;
        free(current);
        current = next_node;
    } while (current != head);
}