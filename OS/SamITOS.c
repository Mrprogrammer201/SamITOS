#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#define SAMITOS_MAX_INPUT 256
#define MAX_FILES 100
#define MAX_PROCESSES 100

typedef struct {
    char name[50];
    int id;
} Process;

typedef struct {
    char name[50];
    char content[1024];
} File;

Process processes[MAX_PROCESSES];
File files[MAX_FILES];
int process_count = 0;
int file_count = 0;
int next_process_id = 1;

void print_samitos_ascii() {
    printf("SSSSS   AAAAA  M     M III  TTTTT  OOO  SSSSS \n");
    printf("S       A   A  MM   MM  I     T   O   O S     \n");
    printf(" SSS    AAAAA  M M M M  I     T   O   O SSSSS \n");
    printf("    S   A   A  M  M  M  I     T   O   O     S \n");
    printf("SSSSS   A   A  M     M III    T    OOO  SSSSS \n");
}

void print_system_info() {
    struct utsname uname_info;
    struct sysinfo sys_info;

    if (uname(&uname_info) != 0) {
        perror("uname");
        return;
    }

    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        return;
    }

    long num_processors = sysconf(_SC_NPROCESSORS_ONLN);

    print_samitos_ascii();
    printf("##############################\n");
    printf("        NICOPAT SYSTEM INFO    \n");
    printf("##############################\n");
    printf("Version OS: SamITOS 1.0 Beta\n");
    printf("Architecture: %s\n", uname_info.machine);
    printf("CPU Cores: %ld\n", num_processors);
    printf("Total RAM: %.2f GB\n", sys_info.totalram / 1024.0 / 1024.0 / 1024.0);
    printf("Free RAM: %.2f GB\n", sys_info.freeram / 1024.0 / 1024.0 / 1024.0);
    printf("Uptime: %ld days, %ld hours, %ld minutes\n", sys_info.uptime / 86400, (sys_info.uptime % 86400) / 3600, (sys_info.uptime % 3600) / 60);
    printf("##############################\n");
}

void poweroff() {
    printf("Выключение ПК...\n");
    exit(0);
}

void reboot(char *argv0) {
    printf("Перезагрузка ОС...\n");
    execv(argv0, (char *[]){argv0, NULL});
    perror("Ошибка перезагрузки");
}

void echo(char *message) {
    if (message && *message) {
        printf("%s\n", message);
    } else {
        printf("Ошибка: пустой текст.\n");
    }
}

void ls() {
    printf("Файлы в виртуальной системе:\n");
    if (file_count == 0) {
        printf("(пусто)\n");
    } else {
        for (int i = 0; i < file_count; i++) {
            printf("%s\n", files[i].name);
        }
    }
}

void cr_fl(char *filename) {
    if (!filename) {
        printf("Ошибка: укажите имя файла.\n");
        return;
    }
    if (file_count >= MAX_FILES) {
        printf("Ошибка: превышен лимит файлов.\n");
        return;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("Ошибка: файл с таким именем уже существует.\n");
            return;
        }
    }
    strncpy(files[file_count].name, filename, sizeof(files[file_count].name) - 1);
    files[file_count].name[sizeof(files[file_count].name) - 1] = '\0';
    files[file_count].content[0] = '\0';
    file_count++;
    printf("Файл %s создан.\n", filename);
}

void dl_fl(char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            for (int j = i; j < file_count - 1; j++) {
                files[j] = files[j + 1];
            }
            file_count--;
            printf("Файл %s удален.\n", filename);
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);
}

void read_file(char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("Содержимое файла %s:\n%s\n", filename, files[i].content[0] ? files[i].content : "(пусто)");
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);
}

void write_file(char *filename, char *text) {
    if (!text) {
        printf("Ошибка: пустой текст для записи.\n");
        return;
    }
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            strncat(files[i].content, text, sizeof(files[i].content) - strlen(files[i].content) - 1);
            strncat(files[i].content, "\n", sizeof(files[i].content) - strlen(files[i].content) - 1);
            files[i].content[sizeof(files[i].content) - 1] = '\0';
            printf("Запись добавлена в файл %s.\n", filename);
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);
}

void cr_proc(char *processName) {
    if (!processName) {
        printf("Ошибка: укажите имя процесса.\n");
        return;
    }
    if (process_count >= MAX_PROCESSES) {
        printf("Ошибка: превышен лимит процессов.\n");
        return;
    }
    processes[process_count].id = next_process_id;
    strncpy(processes[process_count].name, processName, sizeof(processes[process_count].name) - 1);
    processes[process_count].name[sizeof(processes[process_count].name) - 1] = '\0';
    process_count++;
    next_process_id++;
    printf("Процесс %s создан с ID %d.\n", processName, next_process_id - 1);
}

void dl_proc(int processId) {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].id == processId) {
            for (int j = i; j < process_count - 1; j++) {
                processes[j] = processes[j + 1];
            }
            process_count--;
            printf("Процесс с ID %d удален.\n", processId);
            return;
        }
    }
    printf("Процесс с ID %d не найден.\n", processId);
}

void ps() {
    printf("Активные процессы:\n");
    if (process_count == 0) {
        printf("(нет активных процессов)\n");
    } else {
        for (int i = 0; i < process_count; i++) {
            printf("ID: %d, Имя: %s\n", processes[i].id, processes[i].name);
        }
    }
}

void clear_screen() {
    system("clear");
}

void help() {
    printf("Доступные команды:\n");
    printf(" poweroff - Выключить ПК\n");
    printf(" reboot - Перезагрузить ОС\n");
    printf(" echo <текст> - Вывести текст\n");
    printf(" ls - Показать файлы\n");
    printf(" cr_fl <имя> - Создать файл\n");
    printf(" dl_fl <имя> - Удалить файл\n");
    printf(" read <имя> - Прочитать файл\n");
    printf(" write <имя> <текст> - Записать в файл\n");
    printf(" cr_proc <имя> - Создать процесс\n");
    printf(" dl_proc <ID> - Удалить процесс\n");
    printf(" ps - Показать активные процессы\n");
    printf(" clear - Очистить экран\n");
    printf(" help - Показать помощь\n");
    printf(" nicopat - Показать информацию о системе\n");
}

void run_command(char *input, char *argv0) {
    char *cmd = strtok(input, " ");
    if (!cmd) return;

    char *arg1 = strtok(NULL, "");

    if (arg1) {
        while (*arg1 == ' ') arg1++;
        if (*arg1 == '\0') arg1 = NULL;
    }

    if (strcmp(cmd, "poweroff") == 0) {
        poweroff();
    } else if (strcmp(cmd, "reboot") == 0) {
        reboot(argv0);
    } else if (strcmp(cmd, "echo") == 0 && arg1) {
        echo(arg1);
    } else if (strcmp(cmd, "ls") == 0) {
        ls();
    } else if (strcmp(cmd, "cr_fl") == 0 && arg1) {
        cr_fl(arg1);
    } else if (strcmp(cmd, "dl_fl") == 0 && arg1) {
        dl_fl(arg1);
    } else if (strcmp(cmd, "read") == 0 && arg1) {
        read_file(arg1);
    } else if (strcmp(cmd, "write") == 0 && arg1) {
        char *arg2 = strchr(arg1, ' ');
        if (arg2) {
            *arg2 = '\0';
            arg2++;
            while (*arg2 == ' ') arg2++;
            if (*arg2 == '\0') arg2 = NULL;
        }
        if (arg2) {
            write_file(arg1, arg2);
        } else {
            printf("Ошибка: не указан текст для записи\n");
        }
    } else if (strcmp(cmd, "cr_proc") == 0 && arg1) {
        cr_proc(arg1);
    } else if (strcmp(cmd, "dl_proc") == 0 && arg1) {
        dl_proc(atoi(arg1));
    } else if (strcmp(cmd, "ps") == 0) {
        ps();
    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } else if (strcmp(cmd, "help") == 0) {
        help();
    } else if (strcmp(cmd, "nicopat") == 0) {
        print_system_info();
    } else {
        printf("Неизвестная команда: %s\n", cmd);
    }
}

int main(int argc, char *argv[]) {
    char input[SAMITOS_MAX_INPUT];

    printf("---SamITOS BETA VERSION---\n");

    while (1) {
        printf("SamITOS$> ");
        if (fgets(input, SAMITOS_MAX_INPUT, stdin) == NULL) break;
        input[strcspn(input, "\n")] = '\0';
        run_command(input, argv[0]);
    }

    return 0;
}
