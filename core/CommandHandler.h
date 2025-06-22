// CommandHandler.h
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Объявления функций
void run_command(char *input);
void print_help(void);
void clear_screen(void);

// Декларации остальных функций
void ls(void);
void cr_fl(char *filename);
void dl_fl(char *filename);
void cr_proc(char *procname);
void dl_proc(int proc_id);
void read_file(char *filename);
void write_file(char *filename, char *content);
void list_processes(void);
void print_system_info(void);
void echo(char *text);
void compile_command(const char *args);

#endif
