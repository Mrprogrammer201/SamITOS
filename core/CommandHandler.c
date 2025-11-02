#include "CommandHandler.h"
#include "FS/FileSystem.h"
#include "Profiles/Profiles.h"
#include "PM/PM.h"
#include "Toolkit/Toolkit.h"
#include "Utils/Nicopat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFFER 512

typedef void (*command_func_t)(char *args);

typedef struct {
    const char *name;
    command_func_t handler;
    const char *description;
} Command;

// ==== Command handlers ====
void cmd_ls(char *args) { system("ls UserFiles"); }
void cmd_touch(char *args) { cr_fl(args); }
void cmd_rm(char *args) { dl_fl(args); }
void cmd_cat(char *args) { read_file(args); }

void cmd_write(char *args) {
    char *space = strchr(args, ' ');
    if (space) {
        *space = '\0';
        write_file(args, space + 1);
    } else {
        puts("Usage: write <file> <text>");
    }
}

void cmd_del_line(char *args) {
    char *space = strchr(args, ' ');
    if (space) {
        *space = '\0';
        delete_line(args, atoi(space + 1));
    } else {
        puts("Usage: del_line <file> <line number>");
    }
}

void cmd_cr_proc(char *args) { cr_proc(args); }
void cmd_dl_proc(char *args) { dl_proc(atoi(args)); }
void cmd_ps(char *args) { list_processes(); }

void cmd_profile_create(char *args) { profile_create(); }
void cmd_profile_list(char *args) { profile_list(); }
void cmd_profile_edit(char *args) { profile_edit(); }
void cmd_profile_del(char *args) { profile_del(); }
void cmd_login(char *args) { user_login(); }
void cmd_logout(char *args) { logout(); }
void cmd_usermode(char *args) { user_mode_prompt(); }

void cmd_nicopat(char *args) { nicopat_show(); }

void cmd_poweroff(char *args) {
    puts("Shutting down the system...");
    system("poweroff");
}

void cmd_reboot(char *args) {
    puts("Rebooting the system...");
    system("reboot");
}

void cmd_exit(char *args) {
    puts("Exiting shell...");
    exit(0);
}

void cmd_clear(char *args) {
    if (system("clear") == -1) perror("Error running clear");
}

void cmd_echo(char *args) {
    if (args && *args) printf("%s\n", args);
    else puts("Error: no text to echo.");
}

void cmd_gcc(char *args) { toolkit_gcc(args); }
void cmd_python(char *args) { toolkit_python(args); }
void cmd_nano(char *args) { toolkit_nano(args); }

void cmd_exec(char *args) {
    char cmd_path[CMD_BUFFER];
    snprintf(cmd_path, sizeof(cmd_path), "UserFiles/%s", args);
    if (system(cmd_path) == -1) {
        printf("sh: %s: command not found\n", args);
    }
}

// ==== Command table ====
Command commands[] = {
    // Files
    {"ls", cmd_ls, "Show file list"},
    {"touch", cmd_touch, "Create a file"},
    {"rm", cmd_rm, "Delete a file"},
    {"cat", cmd_cat, "Read a file"},
    {"write", cmd_write, "Write to a file"},
    {"del_line", cmd_del_line, "Delete a line from a file"},

    // Processes
    {"cr_proc", cmd_cr_proc, "Create a process"},
    {"dl_proc", cmd_dl_proc, "Delete a process"},
    {"ps", cmd_ps, "Show process list"},

    // Profiles
    {"profile_create", cmd_profile_create, "Create profile"},
    {"profile_list", cmd_profile_list, "List profiles"},
    {"profile_edit", cmd_profile_edit, "Edit profile"},
    {"profile_del", cmd_profile_del, "Delete profile"},
    {"UserLogin", cmd_login, "Login to profile"},
    {"Logout", cmd_logout, "Logout from profile"},
    {"UserMode", cmd_usermode, "Show current mode"},

    // System
    {"nicopat", cmd_nicopat, "Show system info"},
    {"poweroff", cmd_poweroff, "Shutdown system"},
    {"reboot", cmd_reboot, "Reboot system"},
    {"exit", cmd_exit, "Exit shell"},

    // General
    {"clear", cmd_clear, "Clear screen"},
    {"echo", cmd_echo, "Output text"},

    // External tools
    {"gcc", cmd_gcc, "Compile a file (UserFiles)"},
    {"python", cmd_python, "Run a Python script (UserFiles)"},
    {"nano", cmd_nano, "Edit a file (UserFiles)"},
};

// ==== Auto-generation help ====
void cmd_help(char *args) {
    printf("\033[1;32mAvailable commands:\033[0m\n");
    size_t num_cmds = sizeof(commands) / sizeof(commands[0]);
    for (size_t i = 0; i < num_cmds; i++) {
        printf(" \033[1;34m%-12s\033[0m %s\n", commands[i].name, commands[i].description);
    }
    printf(" \033[1;34m./<file>\033[0m Execute file from UserFiles\n");
}

// ==== Run command ====
void run_command(char *input) {
    if (!input || !*input) return;

    // Executable files "./..."
    if (strncmp(input, "./", 2) == 0) {
        cmd_exec(input + 2);
        return;
    }

    // Separate the command and arguments
    char *args = strchr(input, ' ');
    if (args) {
        *args = '\0';
        args++;
    } else {
        args = "";
    }

    // help is separate so that it can work with the table
    if (strcmp(input, "help") == 0) {
        cmd_help(args);
        return;
    }

    // Search in the table
    size_t num_cmds = sizeof(commands) / sizeof(commands[0]);
    for (size_t i = 0; i < num_cmds; i++) {
        if (strcmp(input, commands[i].name) == 0) {
            commands[i].handler(args);
            return;
        }
    }

    printf("Command not found: %s\n", input);
}
