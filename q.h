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
    //printf("init");
	printf("initQ\n");
    struct TCB_t* hed = head;
    printf("malloc queue");
	//printf("\n");
    struct queue* newQueue = (struct queue*) malloc(sizeof(struct queue));
    printf("after queue");
    newQueue->elements = hed;
    newQueue->head = hed;
    //printf("return queue");
    return newQueue;
}

void addQ(struct TCB_t* head, struct TCB_t* item) { //Adds a queue item
	//printf("DEBUG:addQ ////\n");	
	//printf("foo\n");
	fflush(stdout); 
	struct TCB_t* temp = head; 
    if(RunQ->head == NULL) { //no items ->insert first item
        RunQ->head = item;
        //debug("head\n");
    }   else {
        //printf("else\n"); 
        if(RunQ->head->next != NULL) {  //more than 1 item in list, insert tcb into Q
            //printf("ELE 3\n");
            item->prev = RunQ->head->prev;
            item->next = RunQ->head; 
            RunQ->head->prev->next = item; 
            RunQ->head->prev = item; 
        }
        else {
            //printf("ELE 2 \n"); //Single item in list, add next item to Q
            RunQ->head->next = item; 
            RunQ->head->prev = item; 
            item->next = RunQ->head; 
            item->prev = RunQ->head;
        }
    }
}

struct TCB_t* delQ(struct TCB_t* head) { //delQ
    //debug("\nDelete Head");
    struct TCB_t* temp = head;
    head = head->next;
    head->prev = NULL;
    //debug("%d", head->payload);
    return temp;
}

void rotateQ(struct TCB_t* head) { 
   RunQ->head = RunQ->head->next;
 //   head->prev = NULL;
}

void printElements (struct queue* que) {
    //printf("\nPrint Elements");
    struct queue* temp = que;
    if (temp->elements != NULL) {
        while (temp->elements->next != NULL) {
            temp->elements = temp->elements->next;
			//printf("item found");
            //printf("\n%d", temp->elements->payload);
        }
    }
}
