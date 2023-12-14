/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:46 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/10/26 15:35:32 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/* int	main(void)
{
	char	src[] = "nerf THIS";
	char	dst[100];

	// memcpy(dst, src, strlen(src) + 1);
	// printf("src: %s\n", src);
	// printf("dest: %s\n", dst);

	ft_memcpy(dst, src, strlen(src) + 1);
	printf("OUR src: %s\n", src);
	printf("OUR dest: %s\n", dst);
} */