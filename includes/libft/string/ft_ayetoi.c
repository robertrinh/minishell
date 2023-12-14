/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ayetoi.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: robertrinh <robertrinh@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:45:46 by robertrinh    #+#    #+#                 */
/*   Updated: 2023/08/03 14:47:27 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* atoi but LONG */
long	ft_ayetoi(const char *str)
{
	long int	i;
	long int	result;
	long int	neg;

	result = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (neg * result);
}
