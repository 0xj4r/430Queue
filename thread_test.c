// Students- Tim Ferguson and Josh Ransom



#include "threads.h"


int globalRuns = 0; // Increment after each run
TCB_t *RunQ;


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
	RunQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(runQ);

	startThread(f1);
	startThread(f2);
	startThread(f3);
	run();

	return 0;
}