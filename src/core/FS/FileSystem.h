#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void ls(void);
void cr_fl(char *filename);
void dl_fl(char *filename);
void read_file(char *filename);
void write_file(char *filename, char *text);
void delete_line(char *filename, int line_number); // Добавляем объявление функции для удаления строки

#endif

