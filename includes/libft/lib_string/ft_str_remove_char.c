/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove_char.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 19:56:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/04 20:06:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*buffer_trailing_string(char *base_input, int remove_len, int i)
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

static char	*insert_buffer(char *base_input, char *buffer, int i)
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

char	*ft_str_remove_char(char *str, int i, char c)
{
	char	*buffer;

	if (str[i] != c)
		return (str);

	buffer = buffer_trailing_string(str, 1, i);
	if (buffer == NULL)
		return (NULL);
	
	str = insert_buffer(str, buffer, i);
	free (buffer);

	ft_realloc(str, ft_strlen(str));
	return (str);
}
