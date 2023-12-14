/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 12:41:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/08/04 16:43:22 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_length(unsigned int num)
{
	int	length;

	length = 0;
	while (num)
	{
		num = num / 16;
		length++;
	}
	return (length);
}

int	print_hex(unsigned int num, const char format)
{
	if (num == 0)
		return (print_char('0'));
	else
	{
		if (num >= 16)
		{
			print_hex(num / 16, format);
			print_hex(num % 16, format);
		}
		else
		{
			if (num < 10)
				print_char(num + '0');
			else
			{
				if (format == 'x')
					print_char(num - 10 + 'a');
				if (format == 'X')
					print_char(num - 10 + 'A');
			}
		}
	}
	return (hex_length(num));
}
