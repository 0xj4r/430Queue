// Students- Tim Ferguson and Josh Ransom



#include "threads.h"


int globalRuns = 0; // Increment after each run
struct queue *RunQ;


void f1(void) {

	int local = 0;

//	if (DEBUG) printf("THREAD 1: STARTED!!!\n");

	for (;;) {
		printf("THREAD 1:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local++;
		sleep(1);
		yield();
		printf("FUNK 1\n");
	}

	return;
}


void f2(void) {
	// Simulate Power of 2
	int local = 2;

//	if (DEBUG) printf("THREAD 2: STARTED!!!\n");

	for (;;) {
		printf("THREAD 2:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);	
		globalRuns++;
		local *= 2;
		sleep(1);
		yield();
		printf("FUNK 2\n");
	}
	
	return;
}

//-----------//
// f3 Method //
//-----------//
void f3(void) {
	// Multiples of 3
	int local = 3;

	printf("THREAD 3: STARTED!!!\n");

	while (1) {
		printf("THREAD 3:\tGLOBAL: %d\tLOCAL: %d\n", globalRuns, local);
		globalRuns++;
		local += 3;
		sleep(1);

		yield();
		printf("YIELD FUNK 3\n");
	}

	return;
}

//-------------//
// main Method //
//-------------//
int main() {
	RunQ = (struct queue*) malloc(sizeof(struct queue));


	RunQ = initQ(RunQ->head);
printf("Starting Test");
	start_thread(f1);
	start_thread(f2);
	start_thread(f3);
	run();

	return 0;
}
