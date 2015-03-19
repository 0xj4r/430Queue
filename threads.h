// Students - Tim Ferguson and Josh Ransom
// Class: CSE430 
// Assignment: Project 2
// Description: threads.h as described in assignment file

#ifndef THREADS_H
#define THREADS_H

//---------------//
// Include Files //
//---------------//
#include "que.h"
#include "tcb.h"


struct queue *runQ;


void start_Thread(void (*function)(void));
void run();
void yield();


void startThread(void (*function)(void)) {
	void *stack = (void *) malloc(8192);
	TCB_t *temp = newItem();
	init_TCB(temp, function, stack, 8192);
	addQueue(RunQ, temp);
	return;
}


void run() {
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->conext));  // start the first thread
	return;
}

//--------------//
// yield Method //
//--------------//
void yield() {
	ucontext_t from, to;	
	getcontext(&from);
	RunQ->header->context = from;
	rotQueue(RunQ);
	to = RunQ->header->context;
	swapcontext(&from, &to);

	return;
}

#endif
