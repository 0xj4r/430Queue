///que.h
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct q {
    struct q* next;
    struct q* prev;
    int payload;
};

struct queue {
    struct q* head;
    struct q* elements;
};

void debug(const char * format, ...) ;
struct q* newItem();
struct queue* initQ(struct q* head);
void addQ(struct q* head,struct q* index);
struct q* delQ(struct q* head);
void rotateQ(struct q* head);
