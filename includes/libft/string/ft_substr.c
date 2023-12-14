/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 14:34:49 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/10 15:33:45 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	strlen = ft_strlen((char *)s);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start >= strlen)
		len = 0;
	else if (len > (strlen - start))
		len = strlen - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

/* 
#include <stdio.h>
int main(void)
{
	char  str[] = "hola";

	printf("%s \n", ft_substr(str, 0, -1));
	return (0);
}
*/