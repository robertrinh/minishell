/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 12:22:45 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/08/04 14:10:35 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length++;
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*result;
	long int	i;

	i = n;
	size = numlen(i);
	result = ft_calloc(sizeof(char), (size + 1));
	if (!result)
		return (NULL);
	if (i == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (i < 0)
		i *= -1;
	while (size--)
	{
		result[size] = i % 10 + '0';
		i = i / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_itoa(-500));
} */
