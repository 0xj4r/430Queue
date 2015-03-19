///que.h
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "TCB.h"

struct q {
	struct TCB_t *header;
};

struct queue {
    struct q* head;
    struct q* elements;
};

void debug(const char * format, ...) ;
struct TCB_t* newItem();
struct queue* initQ(struct q* head);
void addQ(struct q* head,struct TCB_t* index);
struct TCB_t* delQ(struct q* head);
void rotateQ(struct q* head);
