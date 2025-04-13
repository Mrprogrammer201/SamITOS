#include "PM.h"
#include <stdio.h>
#include <string.h>

Process processes[MAX_PROCESSES];
int process_count = 0;
int next_process_id = 1;

void cr_proc(char *processName) {
    if (process_count >= MAX_PROCESSES) return;
    processes[process_count].id = next_process_id;
    strncpy(processes[process_count].name, processName, sizeof(processes[process_count].name) - 1);
    process_count++;
    next_process_id++;
    printf("Процесс %s создан с ID %d.\n", processName, next_process_id - 1);
}

void dl_proc(int processId) {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].id == processId) {
            for (int j = i; j < process_count - 1; j++) {
                processes[j] = processes[j + 1];
            }
            process_count--;
            printf("Процесс с ID %d удален.\n", processId);
            return;
        }
    }
}

void list_processes() {
    printf("Список процессов:\n");
    for (int i = 0; i < process_count; i++) {
        printf("ID: %d, Имя: %s\n", processes[i].id, processes[i].name);
    }
}
