# `Profiles.c` — Documentation

This module implements user profile management for SamITOS. It provides functionality for creating, deleting, editing, logging in, and logging out of user profiles, as well as managing secure password storage via SHA-256 hashing.

---

## Functions

### `void ensure_data_dir()`

Ensures that the `data` directory exists, creating it if necessary.
If creation fails for reasons other than "already exists", the program exits.

---

### `void trim_newline(char* str)`

Removes the trailing newline character from a string (if present).

---

### `void hash_password(const char* password, char* output_hex)`

Hashes a given password using SHA-256 and writes the result as a hex string to `output_hex`.

* **password** — the plain text password.
* **output\_hex** — buffer where the resulting hex string is written (must be large enough).

---

### `int confirm_password(const char* pass1, const char* pass2)`

Compares two strings (passwords) for equality.

* Returns `1` if equal, `0` otherwise.

---

### `int verify_user(const char* username, const char* password)`

Checks if a username and password combination exists in the profile database.

* Returns `1` if credentials are valid, `0` otherwise.

---

### `void profile_create()`

Prompts the user to create a new profile (username + password + confirmation).
Hashes and stores the credentials in the profile database (`data/profiles.db`).

---

### `void profile_list()`

Lists all profiles stored in the database by displaying usernames.

---

### `void profile_del()`

Prompts the user for credentials and removes the corresponding profile from the database if verified.

---

### `void profile_edit()`

Allows updating an existing profile’s username and password after verifying the current credentials.

---

### `void user_login()`

Prompts for credentials and logs the user in if verified.

* Sets `user_mode` to `1`.
* Sets `current_user` to the logged-in username.

---

### `void logout()`

Logs out the current user after confirming their password.

* Resets `user_mode` to `0`.
* Sets `current_user` to `"guest"`.

---

### `void user_mode_prompt()`

Displays a custom shell prompt depending on whether a user is logged in:

* `SamITOS#<username>$>` if logged in.
* `SamITOS$>` otherwise.

---

## Data Structures

### `Profile`

Defined in `Profiles.h`, contains:

```c
typedef struct {
    char username[PROFILE_INPUT_MAX];
    char password[PROFILE_INPUT_MAX];
} Profile;
```

---

## Notes

* All profile data is stored in plain text format with hashed passwords in `data/profiles.db`.
* SHA-256 hashing is implemented via OpenSSL's `EVP` API.
* This system assumes the environment has OpenSSL installed and accessible.
* No concurrency handling or file locking is implemented.
