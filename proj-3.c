// Students- Tim Ferguson and Josh Ransom

#include "threads.h"
#include "sem.h"

#define NUM_ITEMS = 2
int globalRuns = 0;
struct queue *RunQ;//global Q
struct Semaphore* empty;
struct Semaphore* full;
struct Semaphore* mutex1;
struct Semaphore* mutex2;
int buffer[NUM_ITEMS];
int in = 0;
int out = 0;


void producer(void) {
    while (1) {
        P(mutex1);
        P(empty);
        buffer[in] = 1;
        in = (in + 1) % NUM_ITEMS;
        V(full);
        V(mutex1);
        return;
    }
}

void consumer(void) {
    while(1) {
        P(mutex2);
        P(full);
        int item = buffer[out];
        out = (out + 1) % NUM_ITEMS;
        V(empty);
        V(mutex2);
        return;
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
    start_thread(producer);//starting
    start_thread(consumer);//some
    start_thread(consumer);//some
    run();//RUN EM
    return 0;
}

