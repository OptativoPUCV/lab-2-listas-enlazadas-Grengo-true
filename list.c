#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;
    Node * nuevoNodo = createNode(data);
    if (list->head == NULL)
    {
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = list->head;
        list->head->prev = nuevoNodo;
        list->head = nuevoNodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL) return;
    if (list->current == NULL || list->head == NULL)
    {
        pushFront(list, data);
        return;
    }
    
    Node * nuevoNodo= createNode(data);

    if (list->current == list->tail)
    {
        nuevoNodo->prev = list->current;
        list->current->next = nuevoNodo;
        list->tail = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = list->current->next;
        nuevoNodo->prev = list->current;
        list->current->next->prev = nuevoNodo;
        list->current->next = nuevoNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;
    Node * remover = list->current;
    void * data = remover->data;
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    }
    else if (remover == list->head)
    {
        list->head = remover->next;
        list->head->prev = NULL;
        list->current = list->head;
    }
    else if (remover == list->tail)
    {
        list->tail = remover->prev;
        list->tail->next = NULL;
        list->current = list->head;
    }
    else
    {
        remover->prev->next = remover->next;
        remover->next->prev = remover->prev;
        list->current = remover->next;
    }
    free(remover);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}