#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define FILE_DIR "UserFiles"

// остальные объявления функций
void init_fs();
void cr_fl(char *filename);
void read_file(char *filename);
void write_file(char *filename, char *content);
void delete_line(char *filename, int line_num);
void ls();
void dl_fl(char *filename);

#endif
