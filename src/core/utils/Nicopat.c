#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/sysinfo.h>   // Для sysinfo
#include <sys/statvfs.h>   // Для statvfs

// Функция для вызова CPUID
void cpuid(int code, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    asm volatile ("cpuid"
                  : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                  : "0"(code));
}

// Функция для получения информации о процессоре
void get_cpu_info() {
    uint32_t eax, ebx, ecx, edx;
    char brand[49];

    cpuid(0x80000002, &eax, &ebx, &ecx, &edx);
    memcpy(brand, &eax, 4);
    memcpy(brand + 4, &ebx, 4);
    memcpy(brand + 8, &ecx, 4);
    memcpy(brand + 12, &edx, 4);

    cpuid(0x80000003, &eax, &ebx, &ecx, &edx);
    memcpy(brand + 16, &eax, 4);
    memcpy(brand + 20, &ebx, 4);
    memcpy(brand + 24, &ecx, 4);
    memcpy(brand + 28, &edx, 4);

    cpuid(0x80000004, &eax, &ebx, &ecx, &edx);
    memcpy(brand + 32, &eax, 4);
    memcpy(brand + 36, &ebx, 4);
    memcpy(brand + 40, &ecx, 4);
    memcpy(brand + 44, &edx, 4);

    brand[48] = '\0';
    printf("Процессор: %s\n", brand);
}

// Функция для получения информации о памяти
void get_memory_info() {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("Оперативная память: %.2f GB\n", info.totalram / (1024.0 * 1024 * 1024));
    } else {
        printf("Не удалось получить информацию о памяти.\n");
    }
}

// Симуляция информации о диске
void get_disk_info() {
    struct statvfs fs;
    if (statvfs("/", &fs) == 0) {
        printf("Жесткий диск: %.2f GB (свободно: %.2f GB)\n",
            fs.f_blocks * fs.f_frsize / (1024.0 * 1024 * 1024),  // общий размер
            fs.f_bfree * fs.f_frsize / (1024.0 * 1024 * 1024)); // свободное место
    } else {
        printf("Не удалось получить информацию о диске.\n");
    }
}

// Функция для вывода ASCII-арта
void print_samitos_ascii() {
    printf("==============================================\n");
    printf("SSSSS   AAAAA  M     M III  TTTTT  OOO  SSSSS \n");
    printf("S       A   A  MM   MM  I     T   O   O S     \n");
    printf(" SSS    AAAAA  M M M M  I     T   O   O SSSSS \n");
    printf("    S   A   A  M  M  M  I     T   O   O     S \n");
    printf("SSSSS   A   A  M     M III    T    OOO  SSSSS \n");
    printf("==============================================\n");
}

void print_system_info() {
    print_samitos_ascii(); // Печать ASCII-арта
    get_cpu_info();       // Печать информации о процессоре
    get_memory_info();    // Печать информации о памяти
    get_disk_info();      // Печать информации о жестком диске
}
