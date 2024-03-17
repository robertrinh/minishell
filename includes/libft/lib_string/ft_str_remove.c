/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 11:11:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/17 16:19:45 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// TODO add flags to libft makefile

char	*ft_str_remove(char *base_input, const char *remove)
{
	int		i;
	int		j;
	int		remove_index;
	int		remove_len;
	char	*needle;
	char	*buffer;

	needle = ft_strnstr(base_input, remove, ft_strlen(base_input));
	remove_len = ft_strlen(remove);

	// Locate substring
	i = 0;
	while (base_input[i])
	{
		if (base_input[i] == *needle)
			break ;
		i++;
	}
	remove_index = i;

	// buffer chars after needle
	buffer = malloc(sizeof(char *) * ft_strlen(base_input));
	if (buffer == NULL)
		return (NULL);

	j = 0;
	while (base_input[i + remove_len])
	{
		buffer[j] = base_input[i + remove_len];
		j++;
		i++;
	}
	buffer[j] = '\0';

	// incert buffer at needle
	i = remove_index;
	j = 0;
	while (buffer[j])
	{
		base_input[i] = buffer[j];
		i++;
		j++;
	}
	base_input[i] = '\0';

	free(buffer);
	ft_realloc(base_input, ft_strlen(base_input));
    return (base_input);
}
