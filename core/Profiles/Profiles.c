#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <openssl/evp.h>
#include "Profiles.h"

int user_mode = 0;
char current_user[PROFILE_INPUT_MAX] = "guest";

// Make sure the data directory exists
void ensure_data_dir() {
    if (mkdir("data", 0777) == -1 && errno != EEXIST) {
        perror("Failed to create data directory");
        exit(1);
    }
}

// Remove trailing newline
void trim_newline(char* str) {
    str[strcspn(str, "\n")] = 0;
}

// Hash password using SHA-256
void hash_password(const char* password, char* output_hex) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, password, strlen(password));
    EVP_DigestFinal_ex(ctx, hash, &len);
    EVP_MD_CTX_free(ctx);

    for (unsigned int i = 0; i < len; i++) {
        sprintf(output_hex + (i * 2), "%02x", hash[i]);
    }
    output_hex[len * 2] = '\0';
}

// Compare two passwords
int confirm_password(const char* pass1, const char* pass2) {
    return strcmp(pass1, pass2) == 0;
}

// Verify user credentials
int verify_user(const char* username, const char* password) {
    ensure_data_dir();
    FILE* file = fopen(DB_FILE, "r");
    if (!file) return 0;

    char line[256];
    char pattern[256];
    char hashed[65];
    hash_password(password, hashed);

    // Consistent line format
    sprintf(pattern, "{ username: %s | password: %s};", username, hashed);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Create a new profile
void profile_create() {
    ensure_data_dir();

    Profile p;
    char confirm[PROFILE_INPUT_MAX];
    char hashed[65];

    printf("username: ");
    if (!fgets(p.username, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(p.username);

    printf("password: ");
    if (!fgets(p.password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(p.password);

    printf("confirm password: ");
    if (!fgets(confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(confirm);

    if (!confirm_password(p.password, confirm)) {
        printf("Passwords do not match.\n");
        return;
    }

    FILE* file = fopen(DB_FILE, "a");
    if (!file) {
        printf("Failed to open profile database.\n");
        return;
    }

    hash_password(p.password, hashed);
    // Write in consistent format
    fprintf(file, "{ username: %s | password: %s};\n", p.username, hashed);
    fclose(file);
    printf("Profile created.\n");
}

// List all profiles
void profile_list() {
    ensure_data_dir();
    FILE* file = fopen(DB_FILE, "r");
    if (!file) {
        printf("No profiles.\n");
        return;
    }

    char line[256];
    int count = 0;
    char uname[PROFILE_INPUT_MAX], pass[65];

    while (fgets(line, sizeof(line), file)) {
        // Parse line in expected format
        if (sscanf(line, "{ username: %s | password: %s};", uname, pass) == 2) {
            char *semi = strchr(uname, ';');
            if (semi) *semi = '\0';
            printf(" [%d] - %s\n", count++, uname);
        }
    }

    if (count == 0) printf("No profiles.\n");
    fclose(file);
}

// Delete a profile
void profile_del() {
    ensure_data_dir();

    char username[PROFILE_INPUT_MAX], password[PROFILE_INPUT_MAX], confirm[PROFILE_INPUT_MAX];
    char hashed[65];

    printf("username: ");
    if (!fgets(username, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(username);

    printf("password: ");
    if (!fgets(password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(password);

    printf("confirm password: ");
    if (!fgets(confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(confirm);

    if (!confirm_password(password, confirm)) {
        printf("Passwords do not match.\n");
        return;
    }

    hash_password(password, hashed);

    FILE* file = fopen(DB_FILE, "r");
    FILE* temp = fopen("data/temp.db", "w");
    if (!file || !temp) {
        printf("Failed to process database.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    char line[256];
    char pattern[256];
    sprintf(pattern, "{ username: %s | password: %s};", username, hashed);

    while (fgets(line, sizeof(line), file)) {
        if (!strstr(line, pattern)) {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove(DB_FILE) != 0) {
        perror("Failed to remove old database");
    }
    if (rename("data/temp.db", DB_FILE) != 0) {
        perror("Failed to rename temp file");
    }

    printf("Profile deleted.\n");
}

// Edit an existing profile
void profile_edit() {
    ensure_data_dir();

    char username[PROFILE_INPUT_MAX], password[PROFILE_INPUT_MAX], confirm[PROFILE_INPUT_MAX];
    char new_username[PROFILE_INPUT_MAX], new_password[PROFILE_INPUT_MAX], new_confirm[PROFILE_INPUT_MAX];
    char old_hash[65], new_hash[65];

    printf("current username: ");
    if (!fgets(username, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(username);

    printf("current password: ");
    if (!fgets(password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(password);

    printf("confirm current password: ");
    if (!fgets(confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(confirm);

    if (!confirm_password(password, confirm)) {
        printf("Passwords do not match.\n");
        return;
    }

    printf("new username: ");
    if (!fgets(new_username, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(new_username);

    printf("new password: ");
    if (!fgets(new_password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(new_password);

    printf("confirm new password: ");
    if (!fgets(new_confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(new_confirm);

    if (!confirm_password(new_password, new_confirm)) {
        printf("New passwords do not match.\n");
        return;
    }

    hash_password(password, old_hash);
    hash_password(new_password, new_hash);

    FILE* file = fopen(DB_FILE, "r");
    FILE* temp = fopen("data/temp.db", "w");
    if (!file || !temp) {
        printf("Failed to edit profile.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    char line[256];
    char pattern[256];
    sprintf(pattern, "{ username: %s | password: %s};", username, old_hash);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            fprintf(temp, "{ username: %s | password: %s};\n", new_username, new_hash);
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove(DB_FILE) != 0) {
        perror("Failed to remove old database");
    }
    if (rename("data/temp.db", DB_FILE) != 0) {
        perror("Failed to rename temp file");
    }

    printf("Profile updated.\n");
}

// User login
void user_login() {
    ensure_data_dir();

    char username[PROFILE_INPUT_MAX], password[PROFILE_INPUT_MAX], confirm[PROFILE_INPUT_MAX];

    printf("username: ");
    if (!fgets(username, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(username);

    printf("password: ");
    if (!fgets(password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(password);

    printf("confirm password: ");
    if (!fgets(confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(confirm);

    if (!confirm_password(password, confirm)) {
        printf("Passwords do not match.\n");
        return;
    }

    if (verify_user(username, password)) {
        user_mode = 1;
        strncpy(current_user, username, PROFILE_INPUT_MAX);
        printf("Welcome, %s!\n", username);
    } else {
        printf("Invalid credentials.\n");
    }
}

// User logout
void logout() {
    char password[PROFILE_INPUT_MAX], confirm[PROFILE_INPUT_MAX];

    printf("password: ");
    if (!fgets(password, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(password);

    printf("confirm password: ");
    if (!fgets(confirm, PROFILE_INPUT_MAX, stdin)) return;
    trim_newline(confirm);

    if (!confirm_password(password, confirm)) {
        printf("Passwords do not match.\n");
        return;
    }

    user_mode = 0;
    strcpy(current_user, "guest");
    printf("Logged out.\n");
}

// Show the user prompt
void user_mode_prompt() {
    if (user_mode)
        printf("SamITOS#%s$> ", current_user);
    else
        printf("SamITOS$> ");
}
