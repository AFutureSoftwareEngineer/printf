#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier for Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifierfor  Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_m - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_m
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_n;

/**
 * struct converter_m - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct converter_m
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_n *,
			unsigned char, int, int, unsigned char);
} converter_n;

/**
 * struct flag_m - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_m
{
	unsigned char flag;
	unsigned char value;
} flag_n;

int _printf(const char *format, ...);

/* code for Conversion Specifier Functions */
unsigned int convert_c(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_s(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_di(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_x(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_n *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/* Code Handlers */
unsigned char handle_flags(const char *flags, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_n *,
		unsigned char, int, int, unsigned char);

/* code for Modifiers */
unsigned int print_width(buffer_n *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_n *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_n *output, unsigned int printed,
		unsigned char flags, int wid);

/* code for Helper Functions */
buffer_n *init_buffer(void);
void free_buffer(buffer_n *output);
unsigned int _memcpy(buffer_n *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_n *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_n *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

#endif
