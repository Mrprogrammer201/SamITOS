#include "CommandHandler.h"
#include "FS/FileSystem.h"
#include "Profiles/Profiles.h"
#include "PM/PM.h"
#include "Toolkit/Toolkit.h"
#include "Utils/Nicopat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_command(char *input) {
    if (strcmp(input, "ls") == 0) {
        system("ls UserFiles");
    }
    else if (strncmp(input, "touch ", 6) == 0) {
        cr_fl(input + 6);
    }
    else if (strncmp(input, "rm ", 3) == 0) {
        dl_fl(input + 3);
    }
    else if (strncmp(input, "cat ", 4) == 0) {
        read_file(input + 4);
    }
    else if (strncmp(input, "write ", 6) == 0) {
        char *space = strchr(input + 6, ' ');
        if (space) {
            *space = '\0';
            write_file(input + 6, space + 1);
        } else {
            printf("Invalid format: write <file> <text>\n");
        }
    }
    else if (strncmp(input, "del_line ", 9) == 0) {
        char *space = strchr(input + 9, ' ');
        if (space) {
            *space = '\0';
            int line_num = atoi(space + 1);
            delete_line(input + 9, line_num);
        } else {
            printf("Invalid format: del_line <file> <line number>\n");
        }
    }
    else if (strncmp(input, "cr_proc ", 8) == 0) {
        cr_proc(input + 8);
    }
    else if (strncmp(input, "dl_proc ", 8) == 0) {
        dl_proc(atoi(input + 8));
    }
    else if (strcmp(input, "ps") == 0) {
        list_processes();
    }
    else if (strcmp(input, "profile_create") == 0) {
        profile_create();
    }
    else if (strcmp(input, "profile_list") == 0) {
        profile_list();
    }
    else if (strcmp(input, "profile_edit") == 0) {
        profile_edit();
    }
    else if (strcmp(input, "profile_del") == 0) {
        profile_del();
    }
    else if (strcmp(input, "UserLogin") == 0) {
        user_login();
    }
    else if (strcmp(input, "Logout") == 0) {
        logout();
    }
    else if (strcmp(input, "UserMode") == 0) {
        user_mode_prompt();
    }
    else if (strcmp(input, "nicopat") == 0) {
        nicopat_show();
    }
    else if (strcmp(input, "poweroff") == 0) {
        printf("Shutting down the system...\n");
        system("poweroff");
    }
    else if (strcmp(input, "reboot") == 0) {
        printf("Rebooting the system...\n");
        system("reboot");
    }
    else if (strcmp(input, "exit") == 0) {
        printf("Exiting shell...\n");
        exit(0);
    }
    else if (strcmp(input, "help") == 0) {
        print_help();
    }
    else if (strcmp(input, "clear") == 0) {
        system("clear");
    }
    else if (strncmp(input, "echo ", 5) == 0) {
        printf("%s\n", input + 5);
    }
    else if (strncmp(input, "gcc ", 4) == 0) {
        toolkit_gcc(input + 4);
    }
    else if (strncmp(input, "python ", 7) == 0) {
        toolkit_python(input + 7);
    }
    else if (strncmp(input, "nano ", 5) == 0) {
        toolkit_nano(input + 5);
    }
    else if (strncmp(input, "./", 2) == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "UserFiles/%s", input + 2);
        int res = system(cmd);
        if (res == -1) {
            printf("sh: line 1: %s: command not found\n", input);
        }
    }
    else {
        printf("sh: line 1: %s: command not found\n", input);
    }
}

void clear_screen() {
    if (system("clear") == -1) {
        perror("Error running clear command");
    }
}

void print_help() {
    printf("\033[1;32mAvailable commands:\033[0m\n");
    printf("\n\033[1;34m--- Files ---\033[0m\n");
    printf("ls\t\t\tShow file list\n");
    printf("touch <file>\t\tCreate a file\n");
    printf("rm <file>\t\tDelete a file\n");
    printf("cat <file>\t\tRead a file\n");
    printf("write <file> <text>\tWrite to a file\n");
    printf("del_line <file> <#>\tDelete a line from a file\n");
    printf("\n\033[1;34m--- Processes ---\033[0m\n");
    printf("cr_proc <name>\t\tCreate a process\n");
    printf("dl_proc <ID>\t\tDelete a process\n");
    printf("ps\t\t\tShow process list\n");
    printf("\n\033[1;34m--- Profiles ---\033[0m\n");
    printf("profile_create\t\tCreate profile\n");
    printf("profile_list\t\tList profiles\n");
    printf("profile_edit\t\tEdit profile\n");
    printf("profile_del\t\tDelete profile\n");
    printf("UserLogin\t\tLogin to profile\n");
    printf("Logout\t\t\tLogout from profile\n");
    printf("UserMode\t\tShow current mode\n");
    printf("\n\033[1;34m--- System ---\033[0m\n");
    printf("nicopat\t\t\tShow system info\n");
    printf("poweroff\t\tShutdown system\n");
    printf("reboot\t\t\tReboot system\n");
    printf("exit\t\t\tExit shell\n");
    printf("\n\033[1;34m--- General ---\033[0m\n");
    printf("help\t\t\tShow help\n");
    printf("clear\t\t\tClear screen\n");
    printf("echo <text>\t\tOutput text\n");
    printf("\n\033[1;34m--- External tools ---\033[0m\n");
    printf("gcc <src> <opts>\tCompile a file (UserFiles)\n");
    printf("python <script>\t\tRun a Python script (UserFiles)\n");
    printf("nano <file>\t\tEdit a file (UserFiles)\n");
}

void echo(char *text) {
    if (text && *text) {
        printf("%s\n", text);
    } else {
        printf("Error: no text to echo.\n");
    }
}
