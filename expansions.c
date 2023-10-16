#include "shell.h"

/**
 * expand_variable - expand variables
 *
 * @data: pointer to a struct of the program data
 *
 * Return: nothing, but sets errno.
 */

void expand_variable(data_of_program *data)
{
	int a;
	int b;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (a = 0; line[a]; a++)
		if (line[a] == '#')
			line[a--] = '\0';
		else if (line[a] == '$' && line[a + 1] == '?')
		{
			line[a] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + a + 2);
		}
		else if (line[a] == '$' && line[a + 1] == '$')
		{
			line[a] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + a + 2);
		}
		else if (line[a] == '$' && (line[a + 1] == ' ' || line[a + 1] == '\0'))
			continue;
		else if (line[a] == '$')
		{
			for (b = 1; line[a + b] && line[a + b] != ' '; b++)
				expansion[b - 1] = line[a + b];
			temp = env_get_key(expansion, data);
			line[a] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + a + b);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expans aliases

 * @data: pointer to a struct of the program data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int a;
	int b;
	int was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (a = 0; line[a]; a++)
	{
		for (b = 0; line[a + b] && line[a + b] != ' '; b++)
			expansion[b] = line[a + b];
		expansion[b] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + a + b);
			line[a] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 *
 * @buffer: buffer to be filled
 *
 * @str_to_add: string to be copied in the buffer
 *
 * Return: nothing but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length;
	int a;

	length = str_length(buffer);
	for (a = 0; str_to_add[a]; a++)
	{
		buffer[length + a] = str_to_add[a];
	}
	buffer[length + a] = '\0';
	return (length + a);
}
