/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:58 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 15:25:11 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while ((haystack[i + j] == needle[j] && (i + j) < len)
			&& (haystack[i + j] && needle[j]))
		{
			if (haystack[i + j] == '\0')
				return ((char *)haystack);
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

/* #include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*haystack = "get your ass over here";
	char	*needle = "ass";
	char	*location;


	location = ft_strnstr(haystack, needle, 23);
	printf("found the %s in the string! \n");
} */
