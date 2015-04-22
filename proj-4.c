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
int readerNum = 1; 
int writerNum = 1; 


void readerEnter(int id) {
	printf("Reader %d : Enter\n", id);
    P(mutex);
        if (wwc > 0 || wc > 0) {
            rwc++;
            V(mutex);
            P(readerSem);
            rwc--;
        }
    rc++;
    if (rwc > 0 ) {
        V(readerSem);
    }
    else {
        V(mutex);
    }
}

void readerExit(int id) {
    P(mutex);
    rc--;
	printf("Reader %d :  Exit\n", id);
    if (rc == 0 && wwc > 0) {
        V(writerSem);
    }
    else {
        V(mutex);
    }
	
}

void reader(void) 
{
	int id = 0;
	P(mutex); 
	id = readerNum; 
	readerNum++;
	V(mutex);
	printf("Reader %d Starting\n", id);
    while (1) {
        readerEnter(id);
		printf("Reader %d : Reading\n", id);
		sleep(1);
        readerExit(id);
	printf("Reader %d : Waiting\n", id);
    }
}



void writerEnter(int id) {
    printf("Writer %d :  Enter\n", id);
    P(mutex);
    if(rc > 0 || wc > 0 ) {//|| rwc > 0 || wwc > 0) {
        wwc ++;
        V(mutex);
        P(writerSem);
        wwc--;
    }
    wc ++;
    V(mutex);
}

void writerExit(int id) {
	P(mutex);
    wc--;
    if (rwc > 0 ) {
        V(readerSem);
    }
    else if (wwc > 0) { V(writerSem);}
	printf("Writer %d :  Exit\n", id);
}



void writer(void) {
	int id = 0;
	P(mutex); 
	id = writerNum; 
	writerNum++;
	V(mutex);
	printf("Writer %d : Starting \n", id);
    while (1) {
    		writerEnter(id);
		printf("Writer %d : Waiting\n", id);
    		sleep(1);
    		writerExit(id);
	}
}

void startSemaphore(struct Semaphore* sem, int initial) {
    sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    InitSem(sem, initial);
	sem->semQ = (struct queue*) malloc(sizeof(struct queue));
   sem->semQ = initQ(sem->semQ->head);
}


int main() {
    
	readerSem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	InitSem(readerSem, 1);
   	readerSem->semQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
 	readerSem->semQ = initQ(readerSem->semQ->head);
 
	mutex = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	InitSem(mutex, 1); 
	mutex->semQ = (struct queue*) malloc(sizeof(struct queue));
 	mutex->semQ = initQ(mutex->semQ->head);

	writerSem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	InitSem(writerSem, 1); 
	writerSem->semQ = (struct queue*) malloc(sizeof(struct queue));
	writerSem->semQ = initQ(writerSem->semQ->head);
	
//	startSemaphore(readerSem, 1);
//	startSemaphore(writerSem, 1);
//	startSemaphore(mutex, 1);

	
   	RunQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
 	RunQ = initQ(RunQ->head); //get the party rolling
   	printf("Starting Readers and Writers\n");
   
 	start_thread(writer);
	start_thread(writer);
  	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	run();

	printf("EXITING PROGRAM\n");
    return 0;
}

