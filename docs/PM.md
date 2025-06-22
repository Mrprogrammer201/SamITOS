# PM.h — Documentation

This module implements a simple process manager for SamITOS. It stores processes in RAM, creates, deletes, and lists them.

---

## Constants

```c
#define MAX_PROCESSES 100
```

- Maximum number of simultaneously existing processes.

---

## Structures

```c
typedef struct {
int id;
char name[256];
} Process;
```

- `id` — unique process identifier.
- `name` — process name (up to 255 characters).

---

## Variables

```c
Process processes[MAX_PROCESSES];
int process_count;
int next_process_id;
```

- `processes` — array of all active processes.
- `process_count` — the current number of processes.
- `next_process_id` — the ID that will be assigned to the next process created.

---

## Functions

### `void cr_proc(char *processName);`

Creates a new process with the given name.

- Sets a unique ID.
- Limited by `MAX_PROCESSES`.
- Prints a message about creation.

---

### `void dl_proc(int processId);`

Deletes a process by its ID.

- If found, deletes and all subsequent processes are shifted by one position.
- If not found, does nothing (can be extended for error handling).

---

### `void list_processes(void);`

Prints a list of all active processes:

- For each process, displays the `ID` and `Name`.

---

## Notes

- All data is stored in RAM.
- This implementation is suitable for demonstration or simple OS simulators.
