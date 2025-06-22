# `CommandHandler.c` — Documentation

The **CommandHandler** module implements the command line command handler for SamITOS. It interprets user commands and calls the appropriate functions to work with files, processes, profiles, and system functions.

---

## Main functions

### `void run_command(char *input)`

The main function for handling commands.

#### Supported commands:

##### **Files**

| Command | Description |
| ------------------------- | ------------------------------------- |
| `ls` | List files in `UserFiles`. |
| `touch <file>` | Create a file named `<file>`. |
| `rm <file>` | Delete a file `<file>`. |
| `cat <file>` | Print the contents of a file. |
| `write <file> <text>` | Write `<text>` to file. |
| `del_line <file> <number>` | Delete the specified line from file. |

##### **Processes**

| Command | Description |
| --------------- | --------------------------------- |
| `cr_proc <name>` | Create a process named `<name>`. |
| `dl_proc <ID>` | Delete the process with ID `<ID>`. |
| `ps` | Display the list of processes. |

##### **Profiles**

| Command | Description |
| ---------------- | ------------------------------------ |
| `profile_create` | Create a new profile. |
| `profile_list` | Display the list of profiles. |
| `profile_edit` | Edit a profile. |
| `profile_del` | Delete a profile. |
| `UserLogin` | Log in to your account. |
| `Logout` | Log out of your account. |
| `UserMode` | Show the current user mode. |

##### **System**

| Command | Description |
| ---------- | ----------------------------- |
| `nicopat` | Show system information. |
| `poweroff` | Shut down the system. |
| `reboot` | Reboot the system. |
| `exit` | Exit the shell. |

##### **General**

| Command | Description |
| -------------- | ----------------------------- |
| `help` | Show command help. |
| `clear` | Clear the screen. |
| `echo <text>` | Output text to console. |

##### **External utilities**

| Command | Description |
| ------------------- | --------------------------------------------- |
| `gcc <src> <options>` | Compile a file in `UserFiles`. |
| `python <script>` | Run a Python script from `UserFiles`. |
| `nano <file>` | Open a file in the nano editor from `UserFiles`. |
| `./<file>` | Run an executable file from `UserFiles`. |

##### **Unknown commands**

If the command is not recognized, an error message is displayed:
`sh: line 1: <command>: command not found`

---

### `void clear_screen()`

Clears the screen by calling the `clear` command. If the command fails, it prints a message via `perror`.

--

### `void print_help()`

Prints a help table of all available commands with color formatting.

--

### `void echo(char *text)`

Prints the passed text.
If the text is empty, it reports an error:
`Error: no text to echo.`

---

## Dependencies

* **Project modules:**
`FileSystem.h`, `Profiles.h`, `PM.h`, `Toolkit.h`, `Nicopat.h`
* **System calls:**
`system()`, `exit()`, `snprintf()`, `strncpy()`, `strcmp()`, `strncmp()`, `strchr()`, `atoi()`
* **Linux commands:**
`ls`, `poweroff`, `reboot`, `clear`, `gcc`, `python`, `nano`

---

## Notes

* All files are processed in the `UserFiles` directory.
* The `poweroff` and `reboot` commands require administrator rights.
* The module can be easily extended with new commands: just add a new `else if` block.
