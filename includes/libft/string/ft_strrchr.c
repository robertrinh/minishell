/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:35:59 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/01/10 15:29:20 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/* int	main(void)
{
	char	str[] = "raaizou";

	printf("OG %s \n", strrchr(str, 'a'));
	printf("Ours %s \n", ft_strrchr(str, 'a'));
}

//zoekt de LAATSTE char op en print datgene erna helemaal eruit
*/
