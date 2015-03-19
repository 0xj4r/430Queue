// Students- Tim Ferguson and Josh Ransom



#include "threads.h"


int globalRuns = 0; // Students- Tim Ferguson and Josh Ransom



#include "threads.h"


int globalRuns = 0; // Increment after each run
struct queue *RunQ;


void f1(void) {

	int local = 0;

	if (DEBUG) printf("THREAD 1: STARTED!!!\n");

	for (;;) {
		printf("THREAD 1:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local++;
		sleep(1);
		yield();
	}

	return;
}


void f2(void) {
	// Simulate Power of 2
	int local = 2;

	if (DEBUG) printf("THREAD 2: STARTED!!!\n");

	for (;;) {
		printf("THREAD 2:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local *= 2;
		sleep(1);
		yield();
	}
	
	return;
}

//-----------//
// f3 Method //
//-----------//
void f3(void) {
	// Multiples of 3
	int local = 3;

	if (DEBUG) printf("THREAD 3: STARTED!!!\n");

	for (;;) {
		printf("THREAD 3:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);
		globalRuns++;
		local += 3;
		sleep(1);
		yield();
	}

	return;
}

//-------------//
// main Method //
//-------------//
int main() {
	RunQ = (struct TCB_t*) malloc(sizeof(struct TCB_t));

	initQueue(RunQ->head);

	startThread(f1);
	startThread(f2);
	startThread(f3);
	run();

	return 0;
}
TCB_t *RunQ;


void f1(void) {

	int local = 0;

	if (DEBUG) printf("Begin thread 1\n");

	for (;;) {
		printf("Thread 1:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local++;
		sleep(1);
		yield();
	}

	return;
}


void f2(void) {
	// Simulate Power of 2
	int local = 2;

	if (DEBUG) printf("begin thread 2\n");

	for (;;) {
		printf("thread 2:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local *= 2;
		sleep(1);
		yield();
	}
	
	return;
}


void f3(void) {
	// Multiples of 3
	int local = 3;

	if (DEBUG) printf("Begin thread 3 \n");

	for (;;) {
		printf("Thread 3:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);
		globalRuns++;
		local += 3;
		sleep(1);
		yield();
	}

	return;
}


int main() {
	RunQ = (struct q*) malloc(sizeof(struct q));

	initQueue(runQ);

	startThread(f1);
	startThread(f2);
	startThread(f3);
	run();

	return 0;
}