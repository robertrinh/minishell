/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_insert.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/17 10:13:25 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 19:47:32 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../lib_vector/vector.h"

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

/**
 * Inserts a string into a base string at a specified index. Uses vectors.
 * 
 * @param base The base string where the insertion will take place.
 * @param insert The string to insert into the base string.
 * @param i The index at which the insertion should occur.
 * @return A new string with the inserted content or NULL in case of an error.
 */
char	*ft_str_insert(char *base, char *insert, int i)
{
	char	*buffer;
	t_vec	vec_base;

	// Nothing base to insert into
	if (base == NULL || ft_strlen(base) == 0)
		return (insert);

	// Init vector
	if (ft_vec_init(&vec_base, ft_strlen(base)) == false)
		return (NULL);
	int j = 0;
	while (j < i)
	{
		ft_vec_push(&vec_base, base[j]);
		j++;
	}

	// Buffer trailing string
	buffer = buffer_trailing_string(base, i);
	if (buffer == NULL)
	{
		free (base);
		return (NULL);
	}

	// Insert substring
	ft_vec_push_str(&vec_base, insert);

	// Insert buffer
	ft_vec_push_str(&vec_base, buffer);

	free (buffer);
	return (ft_vec_to_str(&vec_base));
}
