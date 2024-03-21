/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:13:25 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/03/21 17:03:27 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*buffer_trailing_string(char *base, int i)
{
	int		j;
	char	*buffer;

	j = 0;
	buffer = malloc(sizeof(char *) * (ft_strlen(base) - i + 1));
	if (buffer == NULL)
		return (NULL);
	while (base[i])
	{
		buffer[j] = base[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

static char	*insert_substring(char *base, char *insert, int i)
{
	int		j;

	j = 0;
	while (insert[j])
	{
		base[i] = insert[j];
		i++;
		j++;
	}
	base[i] = '\0';
	return (base);
}

char	*ft_str_insert(char *base, char *insert, int i)
{
	char	*buffer;

	printf("base: %s, insert: %s, i: %d\n", base, insert, i);
	if (base == NULL || ft_strlen(base) == 0)
		return (insert);
	base = ft_realloc(base, (ft_strlen(base) + ft_strlen(insert) + 1));
	if (base == NULL)
		return (NULL);
	buffer = buffer_trailing_string(base, i);
	if (buffer == NULL)
		return (NULL);
	base = insert_substring(base, insert, i);
	base = ft_strjoin(base, buffer);
	free (buffer);
	return (base);
}
