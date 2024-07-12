/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove_char.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 19:56:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/12 14:39:16 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../lib_vector/vector.h"

static bool	buffer_trailing_string(char *base_input, t_vec *vec, \
	unsigned int i)
{
	unsigned int	remove_len;

	remove_len = 1;
	while (base_input[i + remove_len])
	{
		if (ft_vec_push(vec, base_input[i + remove_len]) == false)
			return (false);
		i++;
	}
	if (ft_vec_push(vec, '\0') == false)
		return (false);
	return (true);
}

static bool	insert_buffer(char *base_input, unsigned int i, t_vec *vec, \
	t_vec *vec_buffer)
{
	unsigned int	j;
	unsigned int	k;

	j = 0;
	while (j < i)
	{
		if (ft_vec_push(vec, base_input[j]) == false)
			return (false);
		j++;
	}
	k = 0;
	while (k < vec_buffer->len)
	{
		if (ft_vec_push(vec, vec_buffer->data[k]) == false)
			return (false);
		k++;
	}
	if (ft_vec_push(vec, '\0') == false)
		return (false);
	return (true);
}

/**
 * Function to remove a specified character from a string at a given index,
 * and return the modified string. If the character at the given index is
 * not the specified character, the original string is returned. This function
 * uses vectors.
 *
 * @param str The input string.
 * @param i The index at which to check and potentially remove the character.
 * @param c The character to be removed if found at the specified index.
 * @return The modified string with the character removed, or the original
 *         string if the character at the index is not the specified character.
 */
char	*ft_str_remove_char(char *str, int i, char c)
{
	t_vec	vec;
	t_vec	vec_buffer;
	char	*new_str;

	if (str[i] != c)
		return (str);
	if (!ft_vec_init(&vec, ft_strlen(str) + 1))
		return (NULL);
	if (!ft_vec_init(&vec_buffer, ft_strlen(str) + 1))
		return (NULL);
	if (buffer_trailing_string(str, &vec_buffer, i) == false)
		return (NULL);
	if (insert_buffer(str, i, &vec, &vec_buffer) == false)
		return (NULL);
	if (vec_buffer.data)
		ft_vec_free(&vec_buffer);
	new_str = ft_strdup(ft_vec_to_str(&vec));
	ft_vec_free(&vec);
	return (new_str);
}
