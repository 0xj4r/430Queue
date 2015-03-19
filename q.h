///que.h
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "TCB.h"



struct queue {
    struct TCB_t* head;
    struct TCB_t* elements;
};

void debug(const char * format, ...) ;
struct TCB_t* newItem();
struct queue* initQ(struct TCB_t* head);
void addQ(struct TCB_t* head,struct TCB_t* index);
struct TCB_t* delQ(struct TCB_t* head);
void rotateQ(struct TCB_t* head);


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

struct TCB_t* newItem()
{
    struct TCB_t* item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
    item->prev = NULL;
    item->next = NULL;
    //item->context = -1;
    return item;
    
}

struct queue* initQ(struct TCB_t* head) {//Creates an empty queue pointed to by head var.
    debug("init");
    struct TCB_t* hed = head;
    debug("malloc queue");
    struct queue* newQueue = (struct queue*) malloc(sizeof(struct queue));
    debug("after queue");
    newQueue->elements = hed;
    newQueue->head = hed;
    debug("return queue");
    return newQueue;
}

void addQ(struct TCB_t* head, struct TCB_t* item) { //Adds a queue item
    struct TCB_t* it = item;
    struct TCB_t* he = head;
   	printf("added new item");
   // printf("\nAdd new Item to queue:\n%d", he->payload);
    while (he->next != NULL) {
        he = he->next;
       // printf("\n%d", he->payload);
    }
    he->next = newItem();
    he->next = it;
    //printf("\n%d", he->next->payload);
	printf("Payload");
}

struct TCB_t* delQ(struct TCB_t* head) {
    debug("\nDelete Head");
    struct TCB_t* temp = head;
    head = head->next;
    head->prev = NULL;
    //debug("%d", head->payload);
    return temp;
}

void rotateQ(struct TCB_t* head) {
    head = head->next;
    head->prev = NULL;
}

void printElements (struct queue* que) {
    printf("\nPrint Elements");
    struct queue* temp = que;
    if (temp->elements != NULL) {
        while (temp->elements->next != NULL) {
            temp->elements = temp->elements->next;
			printf("item found");
            //printf("\n%d", temp->elements->payload);
        }
    }
}