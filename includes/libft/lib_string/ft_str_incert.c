/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_incert.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 10:13:25 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/18 19:39:09 by quentinbeuk   ########   odam.nl         */
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

static char	*incert_substring(char *base, char *incert, int i)
{
	int		j;

	j = 0;
	while (incert[j])
	{
		base[i] = incert[j];
		i++;
		j++;
	}
	base[i] = '\0';
	return (base);
}

char	*ft_str_incert(char *base, char *incert, int i)
{
	char	*buffer;

	if (base == NULL)
		return (incert);
	base = ft_realloc(base, (ft_strlen(base) + ft_strlen(incert) + 1));
	if (base == NULL)
		return (NULL);
	buffer = buffer_trailing_string(base, i);
	if (buffer == NULL)
		return (NULL);
	base = incert_substring(base, incert, i);
	base = ft_strjoin(base, buffer);
	free (buffer);
	return (base);
}
