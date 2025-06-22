# Nicopat.c — Documentation

The `Nicopat` module implements a `neofetch` style system information display utility for SamITOS. It outputs ASCII art, system information, device information, and is used to visually identify SamITOS.

---

## Constants

```c
#define MAX_OUTPUT 256
```

Maximum string length for storing command output.

```c
const char *COLOR_BLUE
const char *COLOR_RESET
```

ANSI escape codes for formatting output color.

```c
const char *HOST
const char *MODE
const char *OS
const char *LANGUAGE
```

Static system information:

* `HOST`: hostname (e.g. `SamITOS`)
* `MODE`: mode (e.g. `CLI`)
* `OS`: OS version (e.g. `SamITOS - 0.3`)
* `LANGUAGE`: programming language (e.g. `Clang | 100%`)

```c
const char *CMD_CPU
const char *CMD_CORES
const char *CMD_MEM
const char *CMD_GPU
const char *CMD_DEVICES
```

Commands to get system information:

* `CMD_CPU`: command to print CPU model
* `CMD_CORES`: command to count number of cores
* `CMD_MEM`: command to display the amount of RAM
* `CMD_GPU`: command to get the GPU model
* `CMD_DEVICES`: command to list storage devices

---

## Functions

### `void get_cmd_output(const char *cmd, char *output, size_t max_len)`

Executes a system command and writes the first output to the buffer.

**Parameters:**

* `cmd` is the command to execute.
* `output` is the buffer to store the result in.
* `max_len` is the maximum length of the buffer.

If the command does not return a result, the buffer is filled with the string `"Unavailable"`.

---

### `void print_samitos_ascii()`

Prints ASCII art of the SamITOS logo with blue coloring for the CLI.

---

### `void print_info_table()`

Prints system information in a table:

* Host
* Mode
* OS
* Programming language
* CPU model and number of cores
* RAM size
* GPU model
* List of storage devices

Calls system commands and formats the result for the CLI.

--

### `void nicopat_show()`

The main call to Nicopat:

1. Prints ASCII art with `print_samitos_ascii()`.
2. Prints system information with `print_info_table()`.

--

## Dependencies

Requires the following utilities to work:

* `grep`
* `awk`
* `cut`
* `lsblk`
* `lspci`
* `nproc`

Also requires access to `/proc` to read CPU and memory information.

---

## Example output

```
|==============================================|
|SSSSS   AAAAA  M     M III  TTTTT  OOO  SSSSS |
|S       A   A  MM   MM  I     T   O   O S     |
| SSS    AAAAA  M M M M  I     T   O   O SSSSS |
|    S   A   A  M  M  M  I     T   O   O     S |
|SSSSS   A   A  M     M III    T    OOO  SSSSS |
|==============================================|

HOST: SamITOS
MODE: CLI
OS: SamITOS - 0.3
Programming Lang: Clang | 100%
CPU: Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz (8 cores)
RAM: 15.58 GB
GPU: NVIDIA Corporation GP107M [GeForce GTX 1050 Ti Mobile]
Devices:
/dev/sda 465.8G Samsung SSD
/dev/sdb 931.5G WDC WD10EZEX
```
