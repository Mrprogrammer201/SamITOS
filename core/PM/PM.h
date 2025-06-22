#ifndef PM_H
#define PM_H

#define MAX_PROCESSES 50

typedef struct {
    int id;
    char name[50];
} Process;

extern Process processes[MAX_PROCESSES];
extern int process_count;

void list_processes();

#endif
