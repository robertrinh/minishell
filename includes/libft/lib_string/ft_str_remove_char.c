/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_remove_char.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 19:56:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 15:28:52 by quentinbeuk   ########   odam.nl         */
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

static bool insert_buffer(char *base_input, unsigned int i, t_vec *vec, \
	t_vec *vec_buffer)
{
	unsigned int j;
	unsigned int k;

	// Fill vec with base_input until the position before the character to remove
	j = 0;
	while (j < i)
	{
		if (ft_vec_push(vec, base_input[j]) == false)
			return (false);
		j++;
	}

	// Add buffer after the character to remove
	k = 0;
	while (k < vec_buffer->len)
	{
		if (ft_vec_push(vec, vec_buffer->data[k]) == false)
			return (false);
		k++;
	}

	// Null-terminate the vector
	if (ft_vec_push(vec, '\0') == false)
		return (false);

	return (true);
}


char	*ft_str_remove_char(char *str, int i, char c)
{
	t_vec 	vec;
	t_vec 	vec_buffer;
	char 	*result;

	// Check first char is quote
	if (str[i] != c)
		return (str);

	// Init vec
	if (!ft_vec_init(&vec, ft_strlen(str) + 1))
		return (NULL);
	if (!ft_vec_init(&vec_buffer, ft_strlen(str) + 1))
		return (NULL);

	// Buffer chars after quote
	if (buffer_trailing_string(str, &vec_buffer, i) == false)
		return (NULL);

	// Insert buffer back into the vector
	if (insert_buffer(str, i, &vec, &vec_buffer) == false)
		return (NULL);
	
	// Get the final string and free the main vector
	result = ft_get_str(&vec);

	ft_free_vector(&vec_buffer);
	
	return (result);
}
