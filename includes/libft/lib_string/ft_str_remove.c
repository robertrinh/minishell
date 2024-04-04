/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 11:11:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/04 20:02:20 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	locate_substring(char *base_input, const char *needle)
{
	int		i;

	i = 0;
	while (base_input[i])
	{
		if (base_input[i] == *needle)
			break ;
		i++;
	}
	return (i);
}

char	*buffer_trailing_string(char *base_input, int remove_len, int i)
{
	int		j;
	char	*buffer;

	j = 0;
	buffer = malloc(sizeof(char *) * ft_strlen(base_input));
	if (buffer == NULL)
		return (NULL);
	while (base_input[i + remove_len])
	{
		buffer[j] = base_input[i + remove_len];
		j++;
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

char	*insert_buffer(char *base_input, char *buffer, int i)
{
	int		j;

	j = 0;
	while (buffer[j])
	{
		base_input[i] = buffer[j];
		i++;
		j++;
	}
	base_input[i] = '\0';
	return (base_input);
}

char	*ft_str_remove(char *base_input, const char *remove)
{
	int		i;
	int		remove_len;
	char	*needle;
	char	*buffer;

	needle = ft_strnstr(base_input, remove, ft_strlen(base_input));
	remove_len = ft_strlen(remove);
	i = locate_substring(base_input, needle);
	
	// Base == Remove
	if (ft_strncmp(base_input, remove, ft_strlen(base_input)) == 0)
		return ("");

	// Nothing to buffer
	if ((size_t)(i + remove_len) == ft_strlen(base_input))
		return (ft_realloc(base_input, (ft_strlen(base_input) - remove_len)));

	buffer = buffer_trailing_string(base_input, remove_len, i);
	if (buffer == NULL)
		return (NULL);

	base_input = insert_buffer(base_input, buffer, i);
	free(buffer);

	ft_realloc(base_input, ft_strlen(base_input));
	return (base_input);
}
