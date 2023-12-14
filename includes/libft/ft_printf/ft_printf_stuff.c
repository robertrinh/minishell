/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_stuff.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: robertrinh <robertrinh@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 21:24:37 by robertrinh    #+#    #+#                 */
/*   Updated: 2023/08/04 15:06:31 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	print_str(char *str)
{
	int	str_len;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	str_len = ft_strlen(str);
	write(1, str, str_len);
	return (str_len);
}

int	print_num(int num)
{
	int		count;
	char	*str;

	count = 0;
	str = ft_itoa(num);
	if (str)
	{
		count += print_str(str);
		free(str);
	}
	return (count);
}
