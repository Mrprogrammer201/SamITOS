#include "FileSystem.h"
#include <stdio.h>
#include <string.h>

#define MAX_FILES 100

// Структура для хранения файлов
typedef struct {
    char name[256];
    char content[1024];  // Пример размера содержимого файла
} File;

// Массив файлов и счетчик файлов
File files[MAX_FILES];
int file_count = 0;

// Функция создания файла
void cr_fl(char *filename) {
    // Проверяем, существует ли файл с таким именем
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("Файл %s уже существует.\n", filename);
            return;
        }
    }

    // Если файл не найден, создаем новый файл
    if (file_count < MAX_FILES) {
        strcpy(files[file_count].name, filename);
        files[file_count].content[0] = '\0';  // Пустое содержимое файла
        file_count++;
        printf("Файл %s создан.\n", filename);
    } else {
        printf("Превышен лимит на количество файлов.\n");
    }
}

// Функция чтения файла
void read_file(char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("%s\n", files[i].content);  // Выводим только содержимое файла
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);  // Сообщение о том, что файл не найден
}

// Функция записи в файл
void write_file(char *filename, char *content) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            // Находим конец текущего содержимого файла и добавляем новую строку с символом новой строки
            strncat(files[i].content, content, sizeof(files[i].content) - strlen(files[i].content) - 1);
            strncat(files[i].content, "\n", sizeof(files[i].content) - strlen(files[i].content) - 1); // Добавляем новую строку
            printf("Запись в файл %s выполнена.\n", filename);
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);
}

// удаление строки
void delete_line(char *filename, int line_num) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            char *content = files[i].content;
            int current_line = 1;
            char new_content[1024] = "";
            char *line_start = content;
            char *line_end;

            while ((line_end = strchr(line_start, '\n')) != NULL) {
                if (current_line != line_num) {
                    strncat(new_content, line_start, line_end - line_start + 1);
                }
                line_start = line_end + 1;
                current_line++;
            }

            // Если строка для удаления была последней
            if (current_line != line_num) {
                strncat(new_content, line_start, strlen(line_start));
            }

            strncpy(files[i].content, new_content, sizeof(files[i].content) - 1);
            printf("Строка %d из файла %s удалена.\n", line_num, filename);
            return;
        }
    }
    printf("Файл %s не найден.\n", filename);
}

// Функция вывода списка файлов
void ls(void) {
    if (file_count == 0) {
        printf("Нет файлов в виртуальной системе.\n");
    } else {
        printf("Файлы в виртуальной системе:\n");
        for (int i = 0; i < file_count; i++) {
            printf("%s\n", files[i].name);
        }
    }
}

// Функция удаления файла
void dl_fl(char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            // Сдвигаем все файлы, чтобы удалить данный
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
