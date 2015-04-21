// Students- Tim Ferguson and Josh Ransom

#include "sem.h"


int globalRuns = 0;
struct queue *RunQ;//global Q
struct Semaphore* mutex;
struct Semaphore* readerSem;
struct Semaphore* writerSem;
int wwc = 0;
int rwc = 0;
int rc =0;
int wc = 0;

void reader(void) {
    while (1) {
        P(mutex);
        if (wwc > 0 || wc > 0) {
            rwc++;
            V(mutex);
            P(readerSem);
            P(mutex);
            rwc--;
        }
        rc++;
        V(mutex);
        P(mutex);
        printf("READER ");
        rc--;
        if (rc == 0 && wwc > 0) {
            V(writerSem);
        }
        return;

    }
}

void writer(void) {
        while (1) {
        P(mutex);
        if(rc > 0 || wc > 0 || rwc > 0 || wwc > 0) {
            wwc ++;
            V(mutex);
            P(writerSem);
            P(mutex);
            wwc--;
        }
        wc ++;
        V(mutex);
        P(mutex);
        printf("WRITER");
        wc--;
        if (rwc > 0 ) {
	int i;
            for ( i =0; i <= rwc; i++) { V(readerSem); }
        }
        else if (wwc > 0) { V(writerSem);}
        V(mutex);
        return;
    }
}




void startSemaphore(struct Semaphore* sem, int initial) {
    sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    sem->semQ = initQ(sem->semQ->head);
    InitSem(sem, initial);
}

int main() {
//    obama = (struct Semaphore*) malloc(sizeof(struct Semaphore));
//    obama->semQ = initQ(obama->head);
//    InitSem(obama, 0);
    startSemaphore(readerSem, 1);
    startSemaphore(mutex, 1);
    startSemaphore(writerSem, 1);
    RunQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
    RunQ = initQ(RunQ->head);//get the party rolling
    printf("Starting Readers and Writers");
    start_thread(reader);
    start_thread(writer);
//    start_thread(reader(2));
//    start_thread(writer(2));
//    start_thread(reader(3));
//    start_thread(writer(3));
    
    run();//RUN EM
    
    return 0;
}

