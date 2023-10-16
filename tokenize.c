#include "shell.h"
/**
 * token_size - separate string using a delimiter
 *
 * @data: pointer
 *
 * Return: array parts of the string
 */
void token_size(data_of_program *data)
{
	char *delimiter = " \t";
	int a, b, counter = 2, Len;

	Len = str_length(data->input_line);
	if (Len)
	{
		if (data->input_line[Len - 1] == '\n')
			data->input_line[Len - 1] = '\0';
	}

	for (a = 0; data->input_line[a]; a++)
	{
		for (b = 0; delimiter[b]; b++)
		{
			if (data->input_line[a] == delimiter[b])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	a = 0;
	data->tokens[a] = str_duplicate(_str_tok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[a++])
	{
		data->tokens[a] = str_duplicate(_str_tok(NULL, delimiter));
	}
}
