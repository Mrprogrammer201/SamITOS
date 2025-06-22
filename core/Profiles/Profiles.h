#ifndef PROFILES_H
#define PROFILES_H

#define PROFILE_INPUT_MAX 64
#define DB_FILE "data/profiles.db"

typedef struct {
    char username[PROFILE_INPUT_MAX];
    char password[PROFILE_INPUT_MAX];
} Profile;

void profile_create();
void profile_list();
void profile_del();
void profile_edit();
void user_login();
void logout();
void user_mode_prompt();

#endif // PROFILES_H
