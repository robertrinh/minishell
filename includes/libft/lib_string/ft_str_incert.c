/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_incert.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 10:13:25 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 16:33:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_str_incert(char *base, char *incert, int i)
{
	int		i_temp;
	int		j;
	char	*buffer;
	
	if (base == NULL)
		return (incert);
	
	base = ft_realloc(base, (ft_strlen(base) + ft_strlen(incert) + 1));
	buffer = malloc(sizeof(char *) * (ft_strlen(base) - i + 1));
	if (buffer == NULL)
		return (NULL);

	i_temp = i;
	j = 0;
	while (base[i_temp])
	{
		buffer[j] = base[i_temp];
		j++;
		i_temp++;
	}
	buffer[j] = '\0';

	j = 0;
	while (incert[j])
	{
		base[i] = incert[j];
		i++;
		j++;
	}
	base[i] = '\0';

	base = ft_strjoin(base, buffer);
	free (buffer);

	return (base);
}
