#include "CommandHandler.h"
#include "utils/Nicopat.h"
#include "FS/FileSystem.h"
#include "PM/PM.h"
#include "boot/bootloader.h"
#include "main.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SAMITOS_MAX_INPUT 256

int main(int argc, char *argv[]) {
    // Запуск загрузчика
    bootloader_main();

    char input[SAMITOS_MAX_INPUT];

    // Вывод приветствия
    printf(">>> SamITOS - OS Simulator [v0.1] <<<\n");

    // Основной цикл ввода команд
    while (1) {
        printf("SamITOS$> ");

        // Чтение ввода
        if (fgets(input, SAMITOS_MAX_INPUT, stdin) == NULL) {
            perror("Error reading input");
            break;
        }

        // Удаление символа новой строки
        input[strcspn(input, "\n")] = '\0';

        // Обработка команды
        run_command(input, argv[0]);
    }

    return 0;
}

