/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:32:16 by kalmheir          #+#    #+#             */
/*   Updated: 2022/05/30 18:48:06 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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
	int		num_args;
	size_t	chars;
	va_list	args;
	char	*valid_flags;

	valid_flags = "cspdiuxX%";
	chars = 0;
	num_args = count_valid_flags(str);
	if (!num_args)
	{
		putstrip(str, 1, &chars);
		return (chars);
	}
	va_start(args, num_args);
	iterator(str, &args, &chars);
	va_end(args);
	return (chars);
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
	char	*valid_flags;

	valid_flags = "cspdiuxX%";
	if (!*str)
		return (0);
	if (ft_strchr(str, '%'))
	{
		if (ft_strchr(valid_flags, *(str + 1)))
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

void	put_charc(char c, size_t *count)
{
	(*count)++;
	write(STDOUT_FILENO, &c, 1);
}
