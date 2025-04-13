#include "bootloader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void get_system_info() {
    char buffer[128];

    // Получаем название процессора
    printf("Processor: ");
    FILE *os = popen("cat /proc/cpuinfo | grep 'model name' | head -n 1 | cut -d ':' -f2", "r");
    if (os) {
        if (fgets(buffer, sizeof(buffer), os) != NULL) {
            printf("%s", buffer);
        } else {
            printf("Unable to retrieve processor information.\n");
        }
        fclose(os);
    } else {
        printf("Error: Unable to run cpuinfo command.\n");
    }

    // Получаем объем оперативной памяти в килобайтах и переводим в гигабайты
    printf("RAM: ");
    os = popen("cat /proc/meminfo | grep MemTotal | awk '{print $2}'", "r");
    if (os) {
        if (fgets(buffer, sizeof(buffer), os) != NULL) {
            long mem_kb = strtol(buffer, NULL, 10);  // Переводим строку в число
            printf("%.2f GB\n", mem_kb / 1024.0 / 1024.0);  // Переводим в гигабайты и выводим
        } else {
            printf("Unable to retrieve RAM information.\n");
        }
        fclose(os);
    } else {
        printf("Error: Unable to run meminfo command.\n");
    }

    // Получаем размер диска в килобайтах и переводим в гигабайты
    printf("Disk Space: ");
    os = popen("df / | tail -n 1 | awk '{print $2}'", "r");  // Получаем размер в килобайтах
    if (os) {
        if (fgets(buffer, sizeof(buffer), os) != NULL) {
            long disk_kb = strtol(buffer, NULL, 10);  // Переводим строку в число
            printf("%.2f GB\n", disk_kb / 1024.0 / 1024.0);  // Переводим в гигабайты и выводим
        } else {
            printf("Unable to retrieve disk space information.\n");
        }
        fclose(os);
    } else {
        printf("Error: Unable to run df command.\n");
    }

    // Делаем паузу перед загрузкой
    sleep(2);
}

void display_loading_screen() {
    // Заголовок с названием системы и версией
    printf("\n    SamITOS - OS Simulator\n");
    printf("    Version: 0.1 (Build 0425)\n");
    printf("    (C) 2025 Mrprogrammer\n");

    // Разделитель
    printf("\n------------------------------\n");

    // Прогресс
    printf("Loading...\n");

    // Прогресс-бар
    printf("\n[");
    for (int i = 0; i < 50; i++) {  // 50 шагов
        usleep(100000);  // Задержка 0.1 секунда
        printf("#");
        fflush(stdout);  // Обновление на экране
    }
    printf("] Done.\n");

    // Финальное сообщение
    printf("\n------------------------------\n");
    printf("System is ready.\n\n");
}

void bootloader_main() {
    // Сначала выводим информацию о ПК
    get_system_info();

    // Затем начинаем загрузку
    display_loading_screen();
}
