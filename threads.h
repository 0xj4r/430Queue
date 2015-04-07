// Students - Tim Ferguson and Josh Ransom


#ifndef THREADS_H
#define THREADS_H


#include "q.h"


extern struct queue *RunQ; //global RunQ 



void start_thread(void (*function)(void));
void run();
void yield();


void start_thread(void (*function)(void)) { //run thread from the tcb
	void *stack = (void *) malloc(8192);
	struct TCB_t *temp = newItem();
	init_TCB(temp, function, stack, 8192);	
	addQ(RunQ->head, temp);
	return;
}


void run() {
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // super secret magic sauce
    swapcontext(&parent, &(RunQ->head->context));  // start the first thread
	return;
}


void yield() { //context switch type of function
	ucontext_t *from, *to;	
	from = &(RunQ->head->context);
	//printf("YIELD\n");	
	rotateQ(RunQ->head);
	to = &(RunQ->head->context);
	swapcontext(from, to);
	return;
}

#endif
