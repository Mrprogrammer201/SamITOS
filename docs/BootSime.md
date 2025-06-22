# `BootSime.c` — Documentation

The **bootloader** module implements a SamITOS bootloader simulator. It displays a boot menu, hardware information, and simulates the OS boot process.

---

## Main functions

### `void bootsime_main()`

The main entry point of the bootloader.

* Displays the boot menu.
* After selection, shows hardware info and the loading screen.
* Clears the screen between stages.

---

### `static void show_boot_menu()`

Displays the boot menu with options:

* **1** — Boot SamITOS.
* **2** — Reboot the system.
* **3** — Power off the system.

The user inputs a digit. It handles the selection and calls system commands `reboot` or `poweroff` if selected.

---

### `static void print_hardware_info()`

Queries the system and displays hardware info:

* **CPU** (via `/proc/cpuinfo`)
* **RAM** (via `/proc/meminfo`)
* **GPU** (via `lspci`)
* **Disks** (via `lsblk`)

Each component shows a status: `[OK]`, `[NOT FOUND]`, or prints the value.

---

### `static void display_loading_screen()`

Simulates a loading screen:

* Displays a progress bar made of `#` symbols.
* Uses `usleep` to create a visual delay effect.

---

### `static int run_command_output(const char *cmd, char *output, size_t max_len)`

Runs a command and retrieves the first line of its output.

* `cmd` — the command to run.
* `output` — buffer for the output.
* `max_len` — buffer size.

Returns `0` on success or `-1` on error.

---

### `static int check_component(const char *cmd)`

Checks if a command produces any output (to verify component presence).

* `cmd` — the command to check.
* Returns `1` if there is output, otherwise `0`.

---

## Dependencies

* Standard headers: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`
* Uses Linux utilities: `grep`, `awk`, `cut`, `lspci`, `lsblk`, `reboot`, `poweroff`

---

## Notes

* The bootloader does not perform a real OS boot; it is a simulation for SamITOS.
* Works only in a Linux environment with access to standard utilities.
* `reboot` and `poweroff` commands require administrator privileges.
