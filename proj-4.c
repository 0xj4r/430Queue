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
	printf("%d:reader start\n", id);
    //printf("VP mutex reader : wc : %d wwc %d\n", wc, wwc);
    P(mutex);
        if (wwc > 0 || wc > 0) {
            rwc++;
            V(mutex);
            P(readerSem);
            //P(mutex);
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
	printf("%d:reader exit\n", id);
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
	printf("Reader Start\n");
    while (1) {
        readerEnter(id);
		printf("%d:reader Between ReadEnter and  ReadExit");
		sleep(1);
        readerExit(id);
    }
}



void writerEnter(int id) {
    printf("%d:writer start\n", id);
    P(mutex);
    //printf("writer P mutex\n");
    if(rc > 0 || wc > 0 ) {//|| rwc > 0 || wwc > 0) {
        wwc ++;
        V(mutex);
        P(writerSem);
//        P(mutex);
        wwc--;
    }
    wc ++;
    V(mutex);
}

void writerExit(int id) {
    
    //printf("VP mutex writer : rc : %d rwc %d\n", rc, rwc);
	P(mutex);
    wc--;
    if (rwc > 0 ) {
        V(readerSem);
    }
    else if (wwc > 0) { V(writerSem);}
	printf("%d:writer Exit\n", id);
    V(mutex);
}



void writer(void) {
	
	int id = 0;
	P(mutex); 
	id = writerNum; 
	writerNum++;
	V(mutex);
	printf("in writer \n");
    while (1) {
    	writerEnter(id);
		printf("%d:writer Between WriteEnter and  WriteExit");
    	sleep(1);
    	writerExit(id);
	}
}

void startSemaphore(struct Semaphore* sem, int initial) {
    sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
    sem->semQ = initQ(sem->semQ->head);
    InitSem(sem, initial);
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

