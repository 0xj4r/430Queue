// Students - Tim Ferguson and Josh Ransom


#ifndef THREADS_H
#define THREADS_H


#include "q.h"


extern struct queue *RunQ; // 



void start_Thread(void (*function)(void));
void run();
void yield();


void startThread(void (*function)(void)) {
	void *stack = (void *) malloc(8192);
	TCB_t *temp = newItem();
	init_TCB(temp, function, stack, 8192);
	addQueue(RunQ->head, temp);
	return;
}


void run() {
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->head->context));  // start the first thread
	return;
}


void yield() {
	ucontext_t from, to;	
	getcontext(&from);
	RunQ->head->context = from;
	rotQueue(RunQ->head);
	to = RunQ->head->context;
	swapcontext(&from, &to);

	return;
}

#endif
