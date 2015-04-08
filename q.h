//Tim Ferguson and Josh Ransom
//que.h
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "TCB.h"

extern struct queue *RunQ; //Global Q

struct queue {  //Queue with TCB inside
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

struct TCB_t* newItem() //NEw Item implementation
{
    struct TCB_t* item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
    item->prev = NULL;
    item->next = NULL;
    //item->context = -1;
    return item;
    
}

struct queue* initQ(struct TCB_t* head) {//Creates an empty queue pointed to by head var.
    struct TCB_t* hed = head;
    struct queue* newQueue = (struct queue*) malloc(sizeof(struct queue));
    newQueue->elements = hed;
    newQueue->head = hed;
    return newQueue;
}

void addQ(struct TCB_t* head, struct TCB_t* item) { //Adds a queue item
	struct TCB_t* temp = head; 
    if(RunQ->head == NULL) { //no items ->insert first item
        RunQ->head = item;
        //debug("head\n");
    }   else {
        if(RunQ->head->next != NULL) {  //more than 1 item in list, insert tcb into Q
            item->prev = RunQ->head->prev;
            item->next = RunQ->head; 
            RunQ->head->prev->next = item; 
            RunQ->head->prev = item; 
        }
        else {
            RunQ->head->next = item; 
            RunQ->head->prev = item; 
            item->next = RunQ->head; 
            item->prev = RunQ->head;
        }
    }
}

struct TCB_t* delQ(struct TCB_t* head) { //delQ
    struct TCB_t* temp = head;
    head = head->next;
    head->prev = NULL;
    return temp;
}

void rotateQ(struct TCB_t* head) { 
   RunQ->head = RunQ->head->next;
}

void printElements (struct queue* que) {
    struct queue* temp = que;
    if (temp->elements != NULL) {
        while (temp->elements->next != NULL) {
            temp->elements = temp->elements->next;
        }
    }
}
