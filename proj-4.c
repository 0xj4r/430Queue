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
    printf("Reader1\n");
	    
    printf("VP mutex reader : wc : %d wwc %d\n", wc, wwc);
    P(mutex);
        printf("Reader2\n");
        if (wwc > 0 || wc > 0) {
            printf("in the if\n");
            rwc++;
            V(mutex);
            P(readerSem);
//            P(mutex);
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
    printf("%d: Reader mutex\n", id);
    P(mutex);
    printf("READER \n");
    rc--;
    if (rc == 0 && wwc > 0) {
        printf("%d: reader 3\n", id);
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
	printf("Reader STart\n");
    while (1) {
        readerEnter(id);
	sleep(1);
        readerExit(id);
    }
}



void writerEnter(int id) {
    printf("%d:writer start\n", id);
    P(mutex);
    printf("writer P mutex\n");
    if(rc > 0 || wc > 0 ) {//|| rwc > 0 || wwc > 0) {
        printf("BIG IF\n");
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
    
    printf("VP mutex writer : rc : %d rwc %d\n", rc, rwc);
P(mutex);
    printf("%d: WRITER\n", id);
    wc--;
    if (rwc > 0 ) {
        V(readerSem);
    }
    else if (wwc > 0) { V(writerSem);}
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
            sleep(1);
            writerExit(id);
	    }
}
void startSemaphore(struct Semaphore* sem, int initial) {
	printf("startSem1\n");
    sem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	printf("complete malloc1\n");
    sem->semQ = initQ(sem->semQ->head);
	printf("complete Init\n");
    InitSem(sem, initial);
	printf("complete INit sem\n");
}


int main() {
	printf("MAIN\n");    
readerSem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
printf("malloc\n");
 
InitSem(readerSem, 1);
    readerSem->semQ = (struct queue*) malloc(sizeof(struct queue)); //aloc Q
printf("init\n");

   readerSem->semQ = initQ(readerSem->semQ->head);
	printf("seaderSem");    
mutex = (struct Semaphore*) malloc(sizeof(struct Semaphore));
InitSem(mutex, 1); 

mutex->semQ = (struct queue*) malloc(sizeof(struct queue));

 mutex->semQ = initQ(mutex->semQ->head);

writerSem = (struct Semaphore*) malloc(sizeof(struct Semaphore));

InitSem(writerSem, 1); 

writerSem->semQ = (struct queue*) malloc(sizeof(struct queue));

writerSem->semQ = initQ(writerSem->semQ->head);



//startSemaphore(readerSem, 1);
	printf("first Sem\n");
   // startSemaphore(mutex, 1);
   // startSemaphore(writerSem, 1);
	printf("MAIN2\n");
	printf("malloc32423\n"); 
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

