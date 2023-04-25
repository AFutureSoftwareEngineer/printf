#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_c - function.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int sol = 0;

	(void)prec;
	(void)len;

	c = va_arg(args, int);

	sol += print_width(output, sol, flags, wid);
	sol += _memcpy(output, &c, 1);
	sol += print_neg_width(output, sol, flags, wid);

	return (sol);
}

/**
 * convert_percent - function.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int sol = 0;

	(void)args;
	(void)prec;
	(void)len;

	sol += print_width(output, sol, flags, wid);
	sol += _memcpy(output, &percent, 1);
	sol += print_neg_width(output, sol, flags, wid);

	return (sol);
}

/**
 * convert_p - function.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int sol = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	sol += convert_ubase(output, address, "0123456789abcdef",
			flags, wid, prec);
	sol += print_neg_width(output, sol, flags, wid);

	return (sol);
}
