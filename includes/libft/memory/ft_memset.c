/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:32:50 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 14:17:18 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char) c;
		i++;
	}
	return (b);
}

/* int	main(void)
{
	char	str[] = "Code Geass";
	char	str1[] = "Code Geass";

	printf("Before memset => %s", str);
	memset(str, 'x', 7);
	printf("\nAfter memset => %s \n", str);

	ft_memset(str1, 'x', 7);
	printf("After OUR memset => %s", str1);
} */

/* void pointer dereferenced naar een unsigned char. 
de c moet je ook unsigned char converten (in de manual)
b + i want je wilt de positie bepalen van b 
in de string om het te converten */