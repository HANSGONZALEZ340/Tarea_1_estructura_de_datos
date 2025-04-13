#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List *) malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL)
        return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL)
        return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;
    Node * new = createNode(data);
    new->next = list->head;
    if (list->head != NULL)
        list->head->prev = new;
    else
        list->tail = new;
    list->head = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) {
        pushFront(list, data);
        return;
    }

    Node * new = createNode(data);
    new->next = list->current->next;
    new->prev = list->current;

    if (list->current->next != NULL)
        list->current->next->prev = new;
    else
        list->tail = new;

    list->current->next = new;
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
    if (list == NULL || list->current == NULL)
        return NULL;

    Node * aux = list->current;
    void * data = aux->data;

    if (aux->prev != NULL)
        aux->prev->next = aux->next;
    else
        list->head = aux->next;

    if (aux->next != NULL) {
        aux->next->prev = aux->prev;
        list->current = aux->next;
    } else {
        list->tail = aux->prev;
        list->current = aux->prev;
    }

    free(aux);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL)
        popFront(list);
}
