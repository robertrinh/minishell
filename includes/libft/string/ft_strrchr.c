/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:59 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/08/04 14:11:25 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
/* int	main(void)
{
	char	str[] = "raaizou";

	printf("OG %s \n", strrchr(str, 'a'));
	printf("Ours %s \n", ft_strrchr(str, 'a'));
}

//zoekt de LAATSTE char op en print datgene erna helemaal eruit
*/
