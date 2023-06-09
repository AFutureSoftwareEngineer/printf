#include "main.h"

unsigned char handle_flags(const char *flag, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - function.
 * @flag: A pointer to a potential string of flags.
 * @index: An index .
 *
 * Return: If flag characters are matched .
 */
unsigned char handle_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - function.
 * @modifier: A pointer .
 * @index: An index .
 *
 * Return: If a lenth modifier is matched.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - function.
 * @args: A va_list.
 * @modifier: A pointer.
 * @index: An index.
 *
 * Return: If a width modifier is matched.
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int val = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}

		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}

	return (val);
}

/**
 * handle_precision - function.
 * @args: A va_list.
 * @modifier: A pointer.
 * @index: An index.
 *
 * Return: If a precision modifier is matched.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int val = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}

		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}

	return (val);
}

/**
 * handle_specifiers - function.
 * @specifier: A pointer.
 *
 * Return: If a conversion function is matched.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
