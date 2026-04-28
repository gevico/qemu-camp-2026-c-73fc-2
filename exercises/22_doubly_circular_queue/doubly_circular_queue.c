#include "doubly_circular_queue.h"

#include <stdlib.h>
#include <stdio.h>

static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    link p = (link)malloc(sizeof(struct node));
    if (p) {
        p->data = data;
        p->prev = NULL;
        p->next = NULL;
    }
    return p;
}

void free_node(link p) {
    if (p) {
        free(p);
    }
}

link search(int key) {
    link p = head->next;
    while (p != tail) {
        if (p->data == key) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void insert(link p) {
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    if (p == NULL || p == head || p == tail) return;
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

void traverse(void (*visit)(link)) {
    link p = head->next;
    while (p != tail) {
        visit(p);
        p = p->next;
    }
}

void destroy(void) {
    link p = head->next;
    while (p != tail) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head->next = tail;
    tail->prev = head;
}