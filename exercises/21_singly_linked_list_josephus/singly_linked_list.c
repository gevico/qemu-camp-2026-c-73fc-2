#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static link head = NULL;

link make_node(unsigned char item) {
    link p = (link)malloc(sizeof(struct node));
    if (p) {
        p->item = item;
        p->next = NULL;
    }
    return p;
}

void free_node(link p) { free(p); }

link search(unsigned char key) {
    link p;
    for (p = head; p != NULL; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

void insert(link p) {
    p->next = head;
    head = p;
}

void delete(link p) {
    if (head == NULL || p == NULL) return;
    
    if (head == p) {
        head = head->next;
        free_node(p);
        return;
    }
    
    link prev = head;
    while (prev->next != NULL && prev->next != p) {
        prev = prev->next;
    }
    
    if (prev->next == p) {
        prev->next = p->next;
        free_node(p);
    }
}

void traverse(void (*visit)(link)) {
    for (link p = head; p != NULL; p = p->next) {
        visit(p);
    }
}

void destroy(void) {
    link p = head;
    while (p != NULL) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head = NULL;
}

void push(link p) {
    p->next = head;
    head = p;
}

link pop(void) {
    if (head == NULL) return NULL;
    
    link p = head;
    head = head->next;
    p->next = NULL;
    return p;
}

void free_list(link list_head) {
    link p = list_head;
    while (p != NULL) {
        link next = p->next;
        free_node(p);
        p = next;
    }
}