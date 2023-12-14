/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:53 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/11/18 15:06:34 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = dst_len;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	if (dstsize > 0)
	{
		while (src[i] && i + dst_len < dstsize - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	if (i < dstsize)
		dst[j] = '\0';
	return (dst_len + src_len);
}
//(if buffer is fucked, you return the dest size)

/* #include <stdio.h> 
#include <string.h> 

int main(void) 
{ 
    char *s = "hello duplicates"; 
    char target[128] = "target buffer#"; 
	char target1[128] = "target buffer#";
     
    printf("Hello World: \"%s\"\n", target); 
    strlcat(target, s, sizeof(target)); 
    printf("Our New target: \"%s\"\n", target); 

	printf("Hello World: \"%s\"\n", target1); 
    ft_strlcat(target1, s, sizeof(target1)); 
    printf("OG New target: \"%s\"\n", target1); 
 
    return (0); 
} */
