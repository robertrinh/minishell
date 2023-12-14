/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:49 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 12:51:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void			*ret;
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	ret = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (source < dest)
	{
		while (len--)
			*(dest + len) = *(source + len);
		return (dst);
	}
	while (len--)
		*dest++ = *source++;
	return (ret);
}

/* #include <stdio.h>
int	main(void)
{
	int	source[10] = {1,2,3,4,5,6,7,8,9,10};
	int	destination[10];
	int	i;

	i = 0;

	//memmove(source+2, source, sizeof(int) * 8);
	ft_memmove(source+2, source, sizeof(int) * 8);
	while (source[i] != '\0')
	{
		printf("source = %d\n", source[i]);
		i++;
	}

} */