#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

/**
 * struct info- struct for the program's data
 *
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _get_line *
 * @command_name: pointer to the first command typed by the user
 *
 * @exec_counter: number of excecuted comands
 *
 * @file_descriptor: file descriptor to the input of commands
 *
 * @tokens: pointer to array of tokenized input
 *
 * @env: copy of the environ
 *
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;


/**
 * struct built_ins - struct for the built_ins
 *
 * @builtin: the name of the builtin
 *
 * @function: function to be called for each builtin
 */
typedef struct built_ins
{
	char *builtin;
	int (*function)(data_of_program *data);
} buil_tins;

void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);
void handle_ctrl_c(int opr UNUSED);
int _get_line(data_of_program *data);
int check_log_ops(char *array_com[], int i, char array_operators[]);
void expand_variable(data_of_program *data);
void expand_alias(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);
void token_size(data_of_program *data);
char *_str_tok(char *line, char *delim);
int execute(data_of_program *data);
int built_ins_list(data_of_program *data);
char **token_size_path(data_of_program *data);
int find_program(data_of_program *data);
void free_array_of_pointers(char **directories);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);
int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);
int built_in_env(data_of_program *data);
int built_in_set_env(data_of_program *data);
int built_in_unset_env(data_of_program *data);
char *env_get_key(char *name, data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);
void print_environ(data_of_program *data);
int _print(char *string);
int _printe(char *string);
int _print_error(int errorcode, data_of_program *data);
int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_reverse(char *string);
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);
int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *alias);
int set_alias(char *alias_string, data_of_program *data);
#endif
