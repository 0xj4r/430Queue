/// que.c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "que.h"



void debug(const char * format, ...) {
    int DEBUG = 1;
//    if (DEBUG) {
//        printf("\nDEBUG:%s", string);
//    }
    va_list args;
    if (DEBUG)
    {
        va_start (args, format);
        vfprintf (stdout, format, args);
        va_end (args);
    }
}

struct q* newItem()
{
    struct q* item = (struct q*) malloc(sizeof(struct q));
    item->prev = NULL;
    item->next = NULL;
    item->payload = -1;
    return item;
    
}

struct queue* initQ(struct q* head) {//Creates an empty queue pointed to by head var.
    debug("init");
    struct q* hed = head;
    debug("malloc queue");
    struct queue* newQueue = (struct queue*) malloc(sizeof(struct queue));
    debug("after queue");
    newQueue->elements = hed;
    newQueue->head = hed;
    debug("return queue");
    return newQueue;
}

void addQ(struct q* head, struct q* item) { //Adds a queue item
    struct q* it = item;
    struct q* he = head;
    printf("\nAdd new Item to queue:\n%d", he->payload);
    while (he->next != NULL) {
        he = he->next;
        printf("\n%d", he->payload);
    }
    he->next = newItem();
    he->next = it;
    printf("\n%d", he->next->payload);
}

struct q* delQ(struct q* head) {
    debug("\nDelete Head");
    struct q* temp = head;
    head = head->next;
    head->prev = NULL;
    debug("%d", head->payload);
    return temp;
}

void rotateQ(struct q* head) {
    head = head->next;
    head->prev = NULL;
}

void printElements (struct queue* que) {
    printf("\nPrint Elements");
    struct queue* temp = que;
    if (temp->elements != NULL) {
        while (temp->elements->next != NULL) {
            temp->elements = temp->elements->next;
            printf("\n%d", temp->elements->payload);
        }
    }
}

int main (){
    struct q* temp = newItem();
    debug("line 55");
    struct q* item = newItem();
    item->payload = 1;
    struct q* item1 = newItem();
    item1->payload = 2;
    struct q* item2 = newItem();
    item2->payload = 3;
    struct q* item3 = newItem();
    item3->payload = 4;
    
    debug("line 65");
    struct queue* newQueue = initQ(item);
    debug("queue initialized");
    addQ(newQueue->head, item1);
//    addQ(newQueue->head, item1);
    struct q* foo = newQueue->head;
    addQ(newQueue->head, item2);
    addQ(newQueue->head, item3);
    temp = delQ(&newQueue->head);
    
    temp = delQ(&newQueue->head);
    printElements(newQueue);
    debug("\nexecution successful");
}