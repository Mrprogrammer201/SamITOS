#include "CommandHandler.h"
#include "FS/FileSystem.h"
#include "PM/PM.h"
#include "utils/Nicopat.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_command(char *input, char *progname) {
    // Команды для работы с файлами
    if (strcmp(input, "ls") == 0) {
        ls();
    } else if (strncmp(input, "cr_fl ", 6) == 0) {
        cr_fl(input + 6);
    } else if (strncmp(input, "dl_fl ", 6) == 0) {
        dl_fl(input + 6);
    } else if (strncmp(input, "read ", 5) == 0) {
        read_file(input + 5);
    } else if (strncmp(input, "write ", 6) == 0) {
      char *space = strchr(input + 6, ' ');
        if (space) {
            *space = '\0';
            write_file(input + 6, space + 1);
        } else {
            printf("Неверный формат команды write <имя файла> <текст>\n");
        }
    } else if (strncmp(input, "del_line ", 9) == 0) {
        char *space = strchr(input + 9, ' ');
        if (space) {
            *space = '\0';
            int line_num = atoi(space + 1);
            delete_line(input + 9, line_num);
        } else {
            printf("Неверный формат команды del_line <имя файла> <номер строки>\n");
        }
    }

    // Команды для работы с процессами
    else if (strncmp(input, "cr_proc ", 8) == 0) {
        cr_proc(input + 8);
    } else if (strncmp(input, "dl_proc ", 8) == 0) {
        dl_proc(atoi(input + 8));
    } else if (strcmp(input, "ps") == 0) {
        list_processes();
    }

    // Команды для системы
    else if (strcmp(input, "nicopat") == 0) {
        print_system_info();
    } else if (strcmp(input, "poweroff") == 0) {
        printf("Выключение системы...\n");
        exit(0);
    } else if (strcmp(input, "reboot") == 0) {
        printf("Перезагрузка системы...\n");
        system("reboot");
    } else if (strcmp(input, "exit") == 0) {
        printf("Выход из оболочки...\n");
        exit(0);
    }

    // Системные команды
    else if (strcmp(input, "help") == 0) {
        print_help();
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    }

    // Команда для вывода текста
    else if (strncmp(input, "echo ", 5) == 0) {
        echo(input + 5);
    }

    // Неизвестные команды
    else {
        printf("Неизвестная команда: %s\n", input);
    }
}

void clear_screen() {
    system("clear");
}

void print_help() {
    printf("Список доступных команд:\n");

    // Команды для работы с файлами
    printf("\n--- Файлы ---\n");
    printf("ls - показать список файлов\n");
    printf("cr_fl <имя файла> - создать файл\n");
    printf("dl_fl <имя файла> - удалить файл\n");
    printf("read <имя файла> - прочитать файл\n");
    printf("write <имя файла> <текст> - записать в файл\n");
    printf("del_line <имя файла> <номер строки> - удалить строку из файла\n");

    // Команды для работы с процессами
    printf("\n--- Процессы ---\n");
    printf("cr_proc <имя процесса> - создать процесс\n");
    printf("dl_proc <ID процесса> - удалить процесс\n");
    printf("ps - показать список процессов\n");

    // Системные команды
    printf("\n--- Система ---\n");
    printf("nicopat - показать информацию о системе\n");
    printf("poweroff - выключить систему\n");
    printf("reboot - перезагрузить систему\n");
    printf("exit - выйти из оболочки\n");

    // Общие команды
    printf("\n--- Общие ---\n");
    printf("help - показать список команд\n");
    printf("clear - очистить экран\n");
    printf("echo <текст> - вывести текст на экран\n");
}

// Функция для команды echo
void echo(char *text) {
    if (text && strlen(text) > 0) {
        printf("%s\n", text);
    } else {
        printf("Ошибка: не указан текст для вывода.\n");
    }
}
