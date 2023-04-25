#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_x - function.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int sol = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		sol += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		sol += convert_ubase(output, num, "0123456789abcdef",
				flags, wid, prec);

	sol += print_neg_width(output, sol, flags, wid);

	return (sol);
}

/**
 * convert_X - function.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int sol = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		sol += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		sol += convert_ubase(output, num, "0123456789ABCDEF",
				flags, wid, prec);

	sol += print_neg_width(output, sol, flags, wid);

	return (sol);
}
