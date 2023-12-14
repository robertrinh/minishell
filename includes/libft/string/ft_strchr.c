/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:52 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 12:25:41 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

/* #include <stdio.h>
#include <string.h>
int main(void)
{
    char    str[] = "r\0aaizou";
	char    str1[] = "teste";

    printf("OG %s \n", strchr(str, 'a'));
	printf("OG %s \n", strchr(str1 ,'e' + 256));
    printf("Ours %s \n", ft_strchr(str,'a'));
	printf("Ours %s \n", ft_strchr(str1 ,'e' + 256));
} */
