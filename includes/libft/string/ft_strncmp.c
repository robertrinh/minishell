/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/10/29 13:25:47 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* #include <string.h>
int	main(void)
{
	char	s1[] = "h";
	char	s2[] = "hh";

	printf("OG Function: %d \n", strncmp(s1, s2, 2));
	printf("Own Function: %d \n", ft_strncmp(s1, s2, 2));	
}
 */