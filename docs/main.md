# `main.c` — Documentation

Main module of **SamITOS — OS Simulator \[v0.3]**. This file contains the main loop of the program, user input handling, and integration with other simulator components.

---

## Main Functions

### `int main(int argc, char *argv[])`

Entry point of the SamITOS simulator.

#### Functionality:

* Initializes the `SIGINT` (Ctrl+C) signal handler so that the program gracefully returns to the shell on interruption.
* Initializes the filesystem using `init_fs()` (creates the `UserFiles` directory if it does not exist).
* Starts the bootloader simulation via `bootsime_main()`.
* Displays a welcome message.
* Starts the main command loop.

#### Main loop:

1. Displays the `SamITOS$>` prompt.
2. Reads user input using `fgets`.
3. Removes the newline character.
4. Skips empty lines.
5. Passes the command to the `run_command` handler.

---

### `void handle_sigint(int sig)`

Signal handler for `SIGINT`.

#### Functionality:

* When Ctrl+C is pressed, it does not terminate the program but returns the user to the SamITOS shell prompt.
* Displays the message:

  ```
  Interrupted. Returning to SamITOS.
  SamITOS$>
  ```

---

## Constants

```c
#define SAMITOS_MAX_INPUT 256
```

Maximum length of the input string entered by the user.

---

## Dependencies

Uses:

* **stdio.h** — input/output
* **stdlib.h** — standard functions
* **string.h** — string handling
* **unistd.h** — sleep, usleep
* **signal.h** — signal handling
* Internal project modules:

  * `CommandHandler.h`
  * `Utils/Nicopat.h`
  * `FS/FileSystem.h`
  * `PM/PM.h`
  * `BootSime/BootSime.h`
  * `main.h`

---

## Notes

* Works in a Linux-like environment.
* Requires access to standard utilities for full functionality (via calls in other modules).
* Does not terminate the shell on Ctrl+C — the shell remains active.
