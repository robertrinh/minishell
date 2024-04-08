/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup_from.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/08 07:41:52 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/08 07:42:11 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
	Duplicate string starting, 'i' to '\0'.
*/
char	*ft_strdup_from(const char *str, int i)
{
	int		j;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (dest == NULL)
		return (NULL);
	j = 0;
	while (str[i])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
