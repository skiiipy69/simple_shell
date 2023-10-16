#include "shell.h"
/**
* _get_line - read one line from the prompt.
*
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int _get_line(data_of_program *data)
{
	int a;
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read;
	a = 0;
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (a = 0; array_commands[a]; a++)
		{
			free(array_commands[a]);
			array_commands[a] = NULL;
		}
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);
		a = 0;
		do {
			array_commands[a] = str_duplicate(_str_tok(a ? NULL : buff, "\n;"));
			a = check_log_ops(array_commands, a, array_operators);
		} while (array_commands[a++]);
	}
	data->input_line = array_commands[0];
	for (a = 0; array_commands[a]; a++)
	{
		array_commands[a] = array_commands[a + 1];
		array_operators[a] = array_operators[a + 1];
	}
	return (str_length(data->input_line));
}
/**
* check_log_ops - checks and split for && and || operators
*
* @array_com: array of the commands.
*
* @a: index in the array_com to be checked
*
* @array_operators: array of the logical operators.
*
* Return: index of the last command in the array_com.
*/
int check_log_ops(char *array_com[], int a, char array_operators[])
{
	char *tmp = NULL;
	int b;
 	for (b = 0; array_com[a] != NULL  && array_com[a][b]; b++)
	{
		if (array_com[a][b] == '&' && array_com[a][b + 1] == '&')
		{
			tmp = array_com[a];
			array_com[a][b] = '\0';
			array_com[a] = str_duplicate(array_com[a]);
			array_com[a + 1] = str_duplicate(tmp + b + 2);
			a++;
			array_operators[a] = '&';
			free(tmp);
			b = 0;
		}
		if (array_com[a][b] == '|' && array_com[a][b + 1] == '|')
		{
			tmp = array_com[a];
			array_com[a][b] = '\0';
			array_com[a] = str_duplicate(array_com[a]);
			array_com[a + 1] = str_duplicate(tmp + b + 2);
			a++;
			array_operators[a] = '|';
			free(tmp);
			b = 0;
		}
	}
	return (a);
}