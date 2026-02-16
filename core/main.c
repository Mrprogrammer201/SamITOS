#include "CommandHandler.h"
#include "Utils/Nicopat.h"
#include "FS/FileSystem.h"
#include "PM/PM.h"
#include "Profiles/Profiles.h"
#include "BootSime/BootSime.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define SAMITOS_MAX_INPUT 256

// Ctrl+C handler
void handle_sigint(int sig) {
    (void)sig;
    printf("\nInterrupted. Returning to SamITOS.\n");
    printf("SamITOS$> ");
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // Set up SIGINT (Ctrl+C) handler
    signal(SIGINT, handle_sigint);

    // Initialize filesystem (create UserFiles if not exists)
    init_fs();

    // Start bootloader simulation
    bootsime_main();

    // Welcome message
    printf(">>> SamITOS - OS Simulator [v0.3] <<<\n");
    printf("Type 'help' for available commands.\n");

    char input[SAMITOS_MAX_INPUT];

    // Main command loop
    while (1) {
        printf("SamITOS$> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nExiting SamITOS.\n");
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Skip empty lines
        if (strlen(input) == 0) {
            continue;
        }

        // Run command handler
        run_command(input);
    }

    return 0;
}
