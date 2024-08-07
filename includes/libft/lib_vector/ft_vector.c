/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vector.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/15 12:37:13 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/07/12 14:12:04 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * ft_vec_free - Frees the memory allocated for the vector.
 * @v: The vector to be freed.
*/
void	ft_vec_free(t_vec *v)
{
	if (v)
	{
		if (v->data)
		{
			free(v->data);
			v->data = NULL;
		}
	}
}

/**
 * ft_vec_init - Initializes a vector with a specified initial capacity.
 * @v: The vector to be initialized.
 * @size: The initial capacity of the vector.
 * 
 * This function allocates memory for the data array within the vector with
 * the specified initial capacity. It also sets the initial length of the
 * vector to 0. If the memory allocation fails, the function returns false.
 * 
 * Return: true if initialization is successful, false otherwise.
*/
bool	ft_vec_init(t_vec *v, unsigned int size)
{
	v->data = malloc(sizeof(char) * size);
	if (!v->data)
		return (false);
	v->len = 0;
	v->capacity = size;
	return (true);
}

/**
 * ft_vec_resize - Doubles the capacity of the vector.
 * @v: The vector to be resized.
 * 
 * This function allocates a new data array with double the capacity of the
 * current array, copies the existing data to the new array, and then frees
 * the old array. If the memory allocation for the new array fails, the
 * function returns false.
 * 
 * Return: true if resizing is successful, false otherwise.
*/
bool	ft_vec_resize(t_vec *v)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (v->capacity * 2));
	if (!tmp)
		return (false);
	ft_memcpy(tmp, v->data, v->len);
	free(v->data);
	v->data = tmp;
	v->capacity *= 2;
	return (true);
}
