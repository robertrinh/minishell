/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:46:35 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 14:34:07 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*ptr;
	size_t	len;

	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len + 1);
	return (ptr);
}

/* #include <stdio.h>
#include <string.h>
int	main(void)
{
	char	str[] = "choco mint";

	printf("OG %s \n", strdup(str));
	printf("Ours %s \n", ft_strdup(str));
} */