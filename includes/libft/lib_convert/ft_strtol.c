/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 11:30:00 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/03/18 10:42:24 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#include <limits.h>

long	int_add_sign(int sign, long int val);

long int	ft_strtol(char *str)
{
	long int	val;
	int			sign;
	int			i;

	val = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		val = val * 10 + (str[i] - '0');
		i++;
	}
	int_add_sign(sign, val);
	return (val);
}

long	int_add_sign(int sign, long int val)
{
	if (sign == -1)
	{
		val = -val;
		if (val < LONG_MIN)
			val = LONG_MIN;
	}
	else
	{
		if (val > LONG_MAX)
			val = LONG_MAX;
	}
	return (val);
}

int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\r'
		|| c == '\f'
		|| c == '\v');
}
