#include "PM.h"
#include <stdio.h>
#include <string.h>

Process processes[MAX_PROCESSES];
int process_count = 0;
int next_process_id = 1;

// Create a new process
void cr_proc(char *processName) {
    if (process_count >= MAX_PROCESSES) return;

    processes[process_count].id = next_process_id;
    strncpy(processes[process_count].name, processName, sizeof(processes[process_count].name) - 1);
    processes[process_count].name[sizeof(processes[process_count].name) - 1] = '\0';

    printf("Process %s created with ID %d.\n", processName, next_process_id);

    process_count++;
    next_process_id++;
}

// Delete a process by ID
void dl_proc(int processId) {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].id == processId) {
            for (int j = i; j < process_count - 1; j++) {
                processes[j] = processes[j + 1];
            }
            process_count--;
            printf("Process with ID %d deleted.\n", processId);
            return;
        }
    }
}

// List all processes
void list_processes() {
    if (process_count == 0) {
        printf("No processes running.\n");
        return;
    }

    printf("Process list:\n");
    for (int i = 0; i < process_count; i++) {
        printf("ID: %d, Name: %s\n", processes[i].id, processes[i].name);
    }
}
