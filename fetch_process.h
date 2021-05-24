#ifndef FETCH_PROCESS_H
#define FETCH_PROCESS_H

typedef struct ProcessList
{
    char *pid;
    struct ProcessList *next;

} ProcessList;

void printPIDList(struct ProcessList *);
ProcessList *fetchProcessList();

int fetchProcess();
int getProcess(char *);

#endif