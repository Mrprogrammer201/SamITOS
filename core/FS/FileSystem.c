#include "FileSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 100
#define MAX_NAME_LEN 256
#define MAX_CONTENT_LEN 1024
#define FILE_DIR "UserFiles"

typedef struct {
    char name[MAX_NAME_LEN];
} File;

static File files[MAX_FILES];
static int file_count = 0;

// Initialize file system directory
void init_fs() {
    struct stat st;
    if (stat(FILE_DIR, &st) == -1) {
        if (mkdir(FILE_DIR, 0700) == -1) {
            perror("Failed to create file system directory");
        }
    }
}

// Create a new file
void cr_fl(char *filename) {
    if (!filename || strlen(filename) == 0) {
        printf("File name not specified.\n");
        return;
    }

    char filepath[MAX_NAME_LEN + 32];
    snprintf(filepath, sizeof(filepath), "%s/%s", FILE_DIR, filename);

    FILE *f = fopen(filepath, "w");
    if (!f) {
        perror("File creation failed");
        return;
    }
    fclose(f);

    if (file_count < MAX_FILES) {
        strncpy(files[file_count].name, filename, MAX_NAME_LEN - 1);
        files[file_count].name[MAX_NAME_LEN - 1] = '\0';
        file_count++;
        printf("File %s created.\n", filename);
    } else {
        printf("File limit exceeded.\n");
    }
}

// Read and print file content
void read_file(char *filename) {
    if (!filename) return;

    char filepath[MAX_NAME_LEN + 32];
    snprintf(filepath, sizeof(filepath), "%s/%s", FILE_DIR, filename);

    FILE *f = fopen(filepath, "r");
    if (!f) {
        printf("File %s not found.\n", filename);
        return;
    }

    char line[MAX_CONTENT_LEN];
    while (fgets(line, sizeof(line), f)) {
        fputs(line, stdout);
    }
    fclose(f);
}

// Append content to a file
void write_file(char *filename, char *content) {
    if (!filename || !content) {
        printf("Usage: write <file> <text>\n");
        return;
    }

    char filepath[MAX_NAME_LEN + 32];
    snprintf(filepath, sizeof(filepath), "%s/%s", FILE_DIR, filename);

    FILE *f = fopen(filepath, "a");
    if (!f) {
        printf("File %s not found.\n", filename);
        return;
    }

    fprintf(f, "%s\n", content);
    fclose(f);
    printf("Written to file %s.\n", filename);
}

// Delete specific line from a file
void delete_line(char *filename, int line_num) {
    if (!filename || line_num < 1) {
        printf("Usage: del_line <file> <line number>\n");
        return;
    }

    char filepath[MAX_NAME_LEN + 32];
    snprintf(filepath, sizeof(filepath), "%s/%s", FILE_DIR, filename);

    char tmp_path[MAX_NAME_LEN + 32 + 5];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", filepath);

    FILE *f = fopen(filepath, "r");
    FILE *tmp = fopen(tmp_path, "w");
    if (!f || !tmp) {
        perror("File open failed");
        if (f) fclose(f);
        if (tmp) fclose(tmp);
        return;
    }

    char line[MAX_CONTENT_LEN];
    int current = 1;
    while (fgets(line, sizeof(line), f)) {
        if (current != line_num) {
            fputs(line, tmp);
        }
        current++;
    }

    fclose(f);
    fclose(tmp);

    if (remove(filepath) == 0 && rename(tmp_path, filepath) == 0) {
        printf("Line %d removed from file %s.\n", line_num, filename);
    } else {
        printf("Error updating file %s.\n", filename);
    }
}

// List files in the file system
void ls() {
    if (file_count == 0) {
        printf("No files in the file system.\n");
    } else {
        printf("Files in the file system:\n");
        for (int i = 0; i < file_count; i++) {
            printf("  %s\n", files[i].name);
        }
    }
}

// Delete a file
void dl_fl(char *filename) {
    if (!filename) return;

    char filepath[MAX_NAME_LEN + 32];
    snprintf(filepath, sizeof(filepath), "%s/%s", FILE_DIR, filename);

    if (remove(filepath) == 0) {
        for (int i = 0; i < file_count; i++) {
            if (strcmp(files[i].name, filename) == 0) {
                for (int j = i; j < file_count - 1; j++) {
                    files[j] = files[j + 1];
                }
                file_count--;
                break;
            }
        }
        printf("File %s deleted.\n", filename);
    } else {
        printf("File %s not found.\n", filename);
    }
}
