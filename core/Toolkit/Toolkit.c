#include "Toolkit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Run gcc with file paths adjusted to UserFiles/
void toolkit_gcc(const char *args) {
    if (args == NULL || strlen(args) == 0) {
        printf("Usage: gcc <source.c> [options]\n");
        return;
    }

    char command[512];
    char modified_args[512] = {0};

    // Copy args so we can modify -o output file path
    strncpy(modified_args, args, sizeof(modified_args) - 1);

    // Find -o and replace output file path with UserFiles/...
    char *o_pos = strstr(modified_args, "-o ");
    if (o_pos) {
        o_pos += 3; // Move to output file name
        while (*o_pos == ' ') o_pos++; // Skip extra spaces

        char tmp[512];
        snprintf(tmp, sizeof(tmp), "UserFiles/%s", o_pos);
        strcpy(o_pos, tmp);
    }

    // Add UserFiles/ prefix to source file
    char src_file[256] = {0};
    sscanf(modified_args, "%s", src_file);
    char src_path[256];
    snprintf(src_path, sizeof(src_path), "UserFiles/%s", src_file);

    snprintf(command, sizeof(command), "gcc %s %s", src_path, modified_args + strlen(src_file));

    printf("Running GCC: %s\n", command);
    int res = system(command);
    if (res == 0) {
        printf("Compilation successful.\n");
    } else {
        printf("Compilation failed.\n");
    }
}

// Run Python script from UserFiles/
void toolkit_python(const char *filename) {
    char command[512];
    snprintf(command, sizeof(command), "python UserFiles/%s", filename);
    printf("Running Python: %s\n", command);
    system(command);
}

// Run nano editor on a file in UserFiles/
void toolkit_nano(const char *filename) {
    char command[512];
    snprintf(command, sizeof(command), "nano UserFiles/%s", filename);
    system(command);
}
