#include "shell.h"
/**
 * _str_tok - separates strings with delimiters
 *
 * @line: It´s pointer to array.
 *
 * @delim: It´s characters.
 *
 * Return: A pointer to the created token
*/
char *_str_tok(char *line, char *delim)
{
	int k;
	static char *str;
	char *pystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (k = 0; delim[k] != '\0'; k++)
		{
			if (*str == delim[k])
			break;
		}
		if (delim[k] == '\0')
			break;
	}
	pystr = str;
	if (*pystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (k = 0; delim[k] != '\0'; k++)
		{
			if (*str == delim[k])
			{
				*str = '\0';
				str++;
				return (pystr);
			}
		}
	}
	return (pystr);
}
