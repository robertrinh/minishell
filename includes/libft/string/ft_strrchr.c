/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:35:59 by qtrinh            #+#    #+#             */
/*   Updated: 2024/01/05 14:05:07 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strrchr(const char *s, char c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return (s[i]);
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
