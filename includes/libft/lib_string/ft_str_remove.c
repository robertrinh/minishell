/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 11:11:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/27 14:00:20 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../lib_vector/vector.h"

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

/**
 * Removes the first occurrence of the substring `remove` from `base_input` 
 * and returns the resulting string. ft_str_remove uses vectors.
 *
 * @param base_input The original string from which the substring will be removed.
 * @param remove The substring to be removed from the original string.
 * @return The modified string with the substring removed, or NULL if an error occurs.
 */
char	*ft_str_remove(char *base_input, const char *remove)
{
	int		i;
	int		remove_len;
	char	*needle;
	char	*leading_substr;
	char	*trailing_substr;
	t_vec	vec;

	needle = ft_strnstr(base_input, remove, ft_strlen(base_input));
	if (needle == NULL)
		return (NULL);
	i = locate_substring(base_input, needle);
	remove_len = ft_strlen(remove);
	if (ft_strncmp(base_input, remove, ft_strlen(base_input)) == 0)
		return ("");
	if (ft_vec_init(&vec, ft_strlen(base_input)) == false)
		return (NULL);
	leading_substr = ft_substr(base_input, 0, i);
	if (leading_substr == NULL)
		return (NULL);
	ft_vec_push_str(&vec, leading_substr);
	free (leading_substr);
	if ((size_t)(i + remove_len) == ft_strlen(base_input))
		return (ft_vec_to_str(&vec));
	trailing_substr = buffer_trailing_string(base_input, remove_len, i);
	if (trailing_substr == NULL)
		return (NULL);
	ft_vec_push_str(&vec, trailing_substr);
	free (trailing_substr);
	return (ft_vec_to_str(&vec));
}
