#include "BootSime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Execute a command and get the first line of its output
static int run_command_output(const char *cmd, char *output, size_t max_len) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return -1;
    if (fgets(output, max_len, fp) == NULL) {
        pclose(fp);
        return -1;
    }
    pclose(fp);
    size_t len = strlen(output);
    // Remove trailing newline
    if (len > 0 && output[len - 1] == '\n') {
        output[len - 1] = '\0';
    }
    return 0;
}

// Check if the command produces any output (component is present)
static int check_component(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return 0;
    char buffer[256];
    int found = (fgets(buffer, sizeof(buffer), fp) != NULL);
    pclose(fp);
    return found;
}

// Print hardware info
static void print_hardware_info() {
    char buffer[256];

    printf("Hardware information detected:\n\n");

    // CPU
    if (check_component("grep 'model name' /proc/cpuinfo")) {
        printf("[OK] CPU detected\n");
        if (run_command_output("grep 'model name' /proc/cpuinfo | head -n1 | cut -d ':' -f2-", buffer, sizeof(buffer)) == 0) {
            printf("CPU:%s\n", buffer);
        } else {
            printf("CPU: Unknown\n");
        }
    } else {
        printf("[NOT FOUND] CPU\n");
    }

    // RAM
    if (check_component("grep MemTotal /proc/meminfo")) {
        printf("[OK] RAM detected\n");
        if (run_command_output("grep MemTotal /proc/meminfo | awk '{print $2}'", buffer, sizeof(buffer)) == 0) {
            long mem_kb = strtol(buffer, NULL, 10);
            printf("RAM: %.2f GB\n", mem_kb / 1024.0 / 1024.0);
        } else {
            printf("RAM: Unknown\n");
        }
    } else {
        printf("[NOT FOUND] RAM\n");
    }

    // GPU
    if (check_component("lspci | grep -i 'vga\\|3d\\|2d'")) {
        printf("[OK] GPU detected\n");
        if (run_command_output("lspci | grep -i 'vga\\|3d\\|2d' | head -n1 | cut -d ':' -f3-", buffer, sizeof(buffer)) == 0) {
            printf("GPU:%s\n", buffer);
        } else {
            printf("GPU: Unknown\n");
        }
    } else {
        printf("[NOT FOUND] GPU\n");
    }

    // Disks
    if (check_component("lsblk -d")) {
        printf("[OK] Disks detected\n");
        printf("Disks:\n");
        if (system("lsblk -d -o NAME,SIZE,MODEL | grep -v loop | awk '{print \"  /dev/\"$1\"  \"$2\"  \"$3}'") == -1) {
            perror("lsblk command failed");
        }
    } else {
        printf("[NOT FOUND] Disks\n");
    }

    printf("\n");
}

// Display loading screen with progress bar
static void display_loading_screen() {
    printf("\nSamITOS - OS Simulator\n");
    printf("Version: 0.3\n");
    printf("Release date: 22.25.06\n");
    printf("Release time: 22:40\n");
    printf("(C) 2025 Mrprogrammer\n");
    printf("\n----------------------------\n");
    printf("Loading...\n\n[");
    for (int i = 0; i < 50; i++) {
        usleep(100000);
        printf("#");
        fflush(stdout);
    }
    printf("] Done.\n");
    printf("\n----------------------------\n");
    printf("System is ready.\n\n");
}

// Bootloader menu
static void show_boot_menu() {
    int choice = 0;

    while (1) {
        printf("\033[2J\033[H");  // Clear screen
        printf("=== SamITOS Bootloader Menu ===\n");
        printf("1. Boot SamITOS\n");
        printf("2. Reboot\n");
        printf("3. Power off\n");
        printf("----------------------------\n");
        printf("Enter your choice (1-3): ");
        fflush(stdout);

        choice = getchar();
        while (getchar() != '\n'); // Clear stdin

        switch (choice) {
            case '1':
                printf("\nBooting SamITOS...\n");
                sleep(1);
                return;
            case '2':
                printf("\nRebooting...\n");
                sleep(1);
                if (system("reboot") == -1) {
                    perror("Failed to reboot");
                }
                exit(0);
            case '3':
                printf("\nShutting down...\n");
                sleep(1);
                if (system("poweroff") == -1) {
                    perror("Failed to power off");
                }
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
                sleep(1);
        }
    }
}

// Main entry point
void bootsime_main() {
    show_boot_menu();
    sleep(1);
    print_hardware_info();
    sleep(2);
    printf("\033[2J\033[H");
    fflush(stdout);
    display_loading_screen();
    printf("\033[2J\033[H");
    fflush(stdout);
}
