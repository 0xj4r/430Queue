// Students- Tim Ferguson and Josh Ransom

#include "threads.h"


int globalRuns = 0;
struct queue *RunQ;//global Q
struct Semaphore* obama;


void f1(void) {
    int localVar = 1;
    while (1) {
        P(obama);
        // Critical Section
        printf("Thread 1:\tGlobal: %d\tLocal: %d\n", globalRuns, localVar);
        globalRuns ++;
        localVar *=2;
        V(obama);
    }
    return;
}

void f2(void) {
    int localVar = 1;
    while (1) {
        P(obama);
        // Critical Section
        printf("Thread 2:\tGlobal: %d\tLocal: %d\n", globalRuns, localVar);
        globalRuns ++;
        localVar *=3;
        V(obama);
    }
    return;
}


void f3(void) {
    int localVar = 1;
    printf("Thread 3: has begun! - This thread multiplies the local variable by the global each time\n");
    
    while (1) {
        printf("Thread 3:\tGlobal: %d\tLocal: %d\n", globalRuns, localVar);
        localVar = localVar*globalRuns;
        globalRuns++;
        sleep(1);
        yield();
        //printf("YIELD FUNK 3\n");
    }
    return;
}


int main() {
    obama = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    obama->semQ = initQ(obama->head);
    InitSem(obama, 0);
    
    RunQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
    
    RunQ = initQ(RunQ->head);//get the party rolling
    
    printf("Starting Threads - Increment global by 1 for each context switch");
    
    start_thread(f1);//starting
    start_thread(f2);//some
//    start_thread(f3);//threads
    run();//RUN EM
    
    return 0;
}

