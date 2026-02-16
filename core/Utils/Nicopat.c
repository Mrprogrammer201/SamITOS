#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT 256

const char *COLOR_BLUE = "\033[1;36m";
const char *COLOR_RESET = "\033[0m";
const char *HOST = "SamITOS";
const char *MODE = "CLI";
const char *OS = "SamITOS - 0.3";
const char *LANGUAGE = "Clang | 100%";
const char *CMD_CPU = "grep 'model name' /proc/cpuinfo | head -n1 | cut -d ':' -f2-";
const char *CMD_CORES = "nproc";
const char *CMD_MEM = "grep MemTotal /proc/meminfo | awk '{printf \"%.2f GB\", $2/1024/1024}'";
const char *CMD_GPU = "lspci | grep -i 'vga\\|3d\\|2d' | head -n1 | cut -d ':' -f3-";
const char *CMD_DEVICES = "lsblk -d -o NAME,SIZE,MODEL | grep -v loop | awk '{print \"  /dev/\"$1\"  \"$2\"  \"$3}'";

// Get output of a shell command
void get_cmd_output(const char *cmd, char *output, size_t max_len) {
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        snprintf(output, max_len, "Unavailable");
        return;
    }

    if (fgets(output, max_len, fp) == NULL) {
        snprintf(output, max_len, "Unavailable");
    } else {
        size_t len = strlen(output);
        if (len > 0 && output[len - 1] == '\n') {
            output[len - 1] = '\0';
        }
    }

    pclose(fp);
}

// Print SamITOS ASCII logo
void print_samitos_ascii() {
    printf("%s", COLOR_BLUE);
    printf("|==============================================|\n");
    printf("|SSSSS   AAAAA  M     M III  TTTTT  OOO  SSSSS |\n");
    printf("|S       A   A  MM   MM  I     T   O   O S     |\n");
    printf("| SSS    AAAAA  M M M M  I     T   O   O SSSSS |\n");
    printf("|    S   A   A  M  M  M  I     T   O   O     S |\n");
    printf("|SSSSS   A   A  M     M III    T    OOO  SSSSS |\n");
    printf("|==============================================|\n");
    printf("%s", COLOR_RESET);
}

// Print system info table
void print_info_table() {
    char cpu[MAX_OUTPUT], cores[MAX_OUTPUT], mem[MAX_OUTPUT], gpu[MAX_OUTPUT];

    get_cmd_output(CMD_CPU, cpu, MAX_OUTPUT);
    get_cmd_output(CMD_CORES, cores, MAX_OUTPUT);
    get_cmd_output(CMD_MEM, mem, MAX_OUTPUT);
    get_cmd_output(CMD_GPU, gpu, MAX_OUTPUT);

    printf("%s%-12s%s%s\n", COLOR_BLUE, "HOST: ", COLOR_RESET, HOST);
    printf("%s%-12s%s%s\n", COLOR_BLUE, "MODE: ", COLOR_RESET, MODE);
    printf("%s%-12s%s%s\n", COLOR_BLUE, "OS: ", COLOR_RESET, OS);
    printf("%s%-12s%s%s\n", COLOR_BLUE, "Programming Lang: ", COLOR_RESET, LANGUAGE);
    printf("%s%-12s%s%s (%s cores)\n", COLOR_BLUE, "CPU:", COLOR_RESET, cpu, cores);
    printf("%s%-12s%s%s\n", COLOR_BLUE, "RAM:", COLOR_RESET, mem);
    printf("%s%-12s%s%s\n", COLOR_BLUE, "GPU:", COLOR_RESET, gpu);
    printf("%s%-12s%s\n", COLOR_BLUE, "Devices:", COLOR_RESET);

    int res = system(CMD_DEVICES);
    if (res == -1) {
        perror("Error running lsblk");
    }

    printf("\n");
}

// Entry point for nicopat output
void nicopat_show() {
    print_samitos_ascii();
    print_info_table();
}
