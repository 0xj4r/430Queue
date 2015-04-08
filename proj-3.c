// Students- Tim Ferguson and Josh Ransom

#include "threads.h"
#include "sem.h"

#define NUM_ITEMS 6

int globalRuns = 0;
struct queue *RunQ;//global Q
struct Semaphore* empty;
struct Semaphore* full;
struct Semaphore* mutex1;
struct Semaphore* mutex2;
int buffah[NUM_ITEMS];
int in = 0;
int out = 0;


void producer(void) {
    while (1) {
	printf("Producer\n"); 
        P(empty);
	buffah[in] = 1;
        in = (in + 1) % NUM_ITEMS;
	sleep(1);	
	printf("MUTeX 1 Called \n");
        V(full);
	printf("FULL CALLED \n");	
    }
}

void consumer(void) {
    while(1) {
	printf("Consumer\n");
        P(full);
	int item = buffah[out];
        out = (out + 1) % NUM_ITEMS;
        printf("Consumer V mutex:\n");
	sleep(1);
	V(empty);
    }
}

int main() {
    //Allocate memory for Semaphores
    empty = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    full = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    mutex1 = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    mutex2 = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    //Initialize Mutexes
    InitSem(empty, NUM_ITEMS);
    InitSem(full, 0);
    InitSem(mutex2, 1);
    InitSem(mutex1, 1);
    
    RunQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
    RunQ = initQ(RunQ->head);//get the party rolling
    printf("Starting Threads - Increment global by 1 for each context switch");
    
    start_thread(producer);//starting
    start_thread(consumer);//some
    start_thread(producer);//starting
    start_thread(consumer);//some
    run();//RUN EM
    return 0;
}

