/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:32:16 by kalmheir          #+#    #+#             */
/*   Updated: 2022/05/15 17:46:07 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

const char	*g_valid_flags = "cspdiuxX%";
size_t	g_chars;

/*
 * Function:  ft_printf
 * --------------------
 * prints a formatted string to stdout that mimics the
 * original printf() from libc
 *
 * parameters:
 *  str: input string, with formatting macros
 *  ...: variadic variables to be inserted into string
 *
 * returns: total number of printed characters
 *
 *
 * Requirements:
 * -------------
 * Doesn't implement the buffer management of printf()
 *
 * Handles the following conversions:
 *  %c: Character
 *  %s: String
 *  %p: Pointer (void * -> hex integer)
 *  %d and %i: Signed Integer
 *  %u: Unsigned Integer
 *  %x: Lowercase Hexadecimal Integer
 *  %X: Uppercase Hexadecimal Integer
 *  %%: Escaped % symbol
 */
int	ft_printf(const char *str, ...)
{
	int	num_args;
	int	*flag_indices;

	g_chars = 0;
	num_args = count_valid_flags(str);
	flag_indices = malloc(num_args * sizeof(int));
	if (!flag_indices && num_args)
		return (0);
	if (!num_args)
	{
		putstrip(str, 1);
		return (g_chars);
	}
}

/*
 * Function:  count_valid_flags
 * --------------------
 * Counts the number of valid formatting flags in a string
 *
 * parameters:
 *  str: input string, with formatting macros
 *
 * returns: total number of valid flags
 */
int	count_valid_flags(const char *str)
{
	if (!*str)
		return (0);
	if (ft_strchr(str, '%'))
	{
		if (ft_strchr(g_valid_flags, *(str + 1)))
			return (1 + count_valid_flags(str + 1));
		return (count_valid_flags(str + 1));
	}
	return (0);
}

/*
 * Function:  ft_strchr
 * --------------------
 * Searches for a character within a string
 *
 * parameters:
 *  s: string to be searched through
 *  c: character to be found
 *
 * returns: pointer to the character within the string
 *  null on failure to find
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (0);
}

/*
 * Function:  putstrip
 * --------------------
 * Prints a string to stdout with the option to ignore
 * percentage signs
 *
 * parameters:
 *  str: string to be printed
 *  ignore_percent: boolean value whether or not to ignore %
 */
void	putstrip(const char *str, char ignore_percent)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && ignore_percent)
		{
			i++;
			continue ;
		}
		proxy_write(str + i, 1);
	}
}

/*
 * Function:  proxy_write
 * --------------------
 * Prints a character to stdout and increments the global
 * counter, used to encapsulate and count write calls
 *
 * parameters:
 *  c: beginning of buffer to be written
 *  amount: number of characters to be written
 */
void	proxy_write(char *c, int amount)
{
	write(STDOUT_FILENO, c, amount);
	g_chars += amount;
}
