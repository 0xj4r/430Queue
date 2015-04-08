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


//void producer(int i) {
//    int local=0;
//    while (1) {
//        P(empty);
//        printf("Producer %d CS Started\n", i);
//        buffah[in] = 1;
//        globalRuns++;
//        local++;
//        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
//        in = (in + 1) % NUM_ITEMS;
//        sleep(1);
//        printf("Producer %d Exited CS", i);
//        V(full);
//    }
//}
//
//void consumer (int i) {
//    int local=0;
//    while(1) {
//        P(full);
//        printf("Consumer %d CS Started\n", i);
//        int item = buffah[out];
//        globalRuns++;
//        local++;
//        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
//        out = (out + 1) % NUM_ITEMS;
//        sleep(1);
//        printf("Consumer %d Exited CS", i);
//        V(empty);
//    }
//}

void producer1(void) {
    int local=0;
    while (1) {
        P(empty);
        printf("Producer 1 CS Started\n");
        buffah[in] = 1;
        globalRuns++;
        local++;
        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
        in = (in + 1) % NUM_ITEMS;
        sleep(1);
        printf("Producer 1 Exited CS");
        V(full);
    }
}

void consumer1 (void) {
    int local=0;
    while(1) {
        P(full);
        printf("Consumer 1 CS Started\n");
        int item = buffah[out];
        globalRuns++;
        local++;
        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
        out = (out + 1) % NUM_ITEMS;
        sleep(1);
        printf("Consumer 2 Exited CS");
        V(empty);
    }
}

void producer2(void) {
    int local=0;
    while (1) {
        P(empty);
        printf("Producer 2 CS Started\n");
        buffah[in] = 1;
        globalRuns++;
        local++;
        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
        in = (in + 1) % NUM_ITEMS;
        sleep(1);
        printf("Producer 2 Exited CS");
        V(full);
    }
}

void consumer2 (void) {
    int local=0;
    while(1) {
        P(full);
        printf("Consumer 2 CS Started\n");
        int item = buffah[out];
        globalRuns++;
        local++;
        printf("Global Runs : %d\tLocal Runs: %d", globalRuns, local)
        out = (out + 1) % NUM_ITEMS;
        sleep(1);
        printf("Consumer 2 Exited CS");
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
    printf("Starting Threads - Increment global by 1 for each context switch\n");
    
//    start_thread((*producer)(1);//starting
//    start_thread((*consumer)(1));//some
//    start_thread((*producer)(2));//starting
//    start_thread((*consumer)(2));//some
    start_thread((producer1);//starting
    start_thread(consumer1);//some
    start_thread(producer2);//starting
    start_thread(consumer2);//some

    run();//RUN EM
    return 0;
}

