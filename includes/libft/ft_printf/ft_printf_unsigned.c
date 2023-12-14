/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_unsigned.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 15:03:07 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/08/04 15:06:38 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(unsigned int num)
{
	int	length;

	length = 0;
	while (num)
	{
		num = num / 10;
		length++;
	}
	return (length);
}

static char	*itoa_unsigned(unsigned int num)
{
	char	*result;
	int		size;

	size = numlen(num);
	result = ft_calloc(sizeof(char), (size + 1));
	if (!result)
		return (NULL);
	while (size--)
	{
		result[size] = num % 10 + '0';
		num = num / 10;
	}
	return (result);
}

int	print_unsigned(unsigned int num)
{
	int		char_count;
	char	*str;

	char_count = 0;
	if (num == 0)
		char_count += print_char('0');
	else
	{
		str = itoa_unsigned(num);
		if (str)
		{
			char_count += print_str(str);
			free (str);
		}
	}
	return (char_count);
}
