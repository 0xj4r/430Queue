// Students - Tim Ferguson and Josh Ransom
// P3


#ifndef SEM_H
#define SEM_H

#include "threads.h"

extern struct queue* RunQ; //Global Run queue.

struct Semaphore {
    struct queue* semQ;
    int value;
};

void InitSem(struct Semaphore* sem, int value) {
    sem->value = value;
    return;
}

void P(struct Semaphore* sem) {
    sem->value--;
	printf("P entered: %d \n", sem->value); 
   if (sem->value < 0) {//Block
		
       // struct queue* tempQ = RunQ;
       printf("temp q \n");
	 struct TCB_t* item = delQ(RunQ->head);
        printf("del q \n");
	addQ(sem->semQ->head, item);
        printf("add q \n");
	swapcontext(&(item->context), &(RunQ->head->context));
    }
//	printf("P1 exited\n");	
    return;
}

void V(struct Semaphore* sem) {
    sem->value++;
	printf("SEM VALUE: %d\n", sem->value);
    if (sem->value < 1) {
        struct TCB_t* temp = delQ(sem->semQ->head);
        addQ(RunQ->head, temp);
	printf("YIELD\n");
    }
yield();
    return;
}


#endif


//Semaphore data structure: A value field and a queue of TCBs.
//
//InitSem(semaphore, value): Initializes the value field with the specified value.
//
//P(semaphore): The P routine decrements the semaphore, and if the value is less than zero then blocks the process in the queue associated with the semaphore.
//
//V(semaphore): The V routine increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queue.
//Note: The V routine also "yields" to the next runnable process. //this is important.
