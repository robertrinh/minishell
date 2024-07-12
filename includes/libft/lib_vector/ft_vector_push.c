/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:57:03 by qtrinh            #+#    #+#             */
/*   Updated: 2024/07/12 16:01:46 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * ft_vec_push - Adds a character to the end of the vector.
 * @v: The vector to which the character will be added.
 * @c: The character to add.
 * 
 * This function adds the specified character to the end of the vector. If
 * the vector is full, it first resizes the vector by doubling its capacity.
 * If the resize operation fails, the function returns false.
 * 
 * Return: true if the character is successfully added, false otherwise.
*/
bool	ft_vec_push(t_vec *v, char c)
{
	if (v->len == v->capacity)
	{
		if (!ft_vec_resize(v))
			return (false);
	}
	v->data[v->len] = c;
	v->len++;
	return (true);
}

/**
 * ft_vec_push_str - Adds a null-terminated string to the end of the vector.
 * @v: The vector to which the string will be added.
 * @str: The null-terminated string to add.
 * 
 * This function appends the specified string to the end of the vector. If
 * the vector does not have enough capacity to accommodate the new string,
 * it resizes the vector by doubling its capacity until there is enough space.
 * If the resize operation fails, the function returns false.
 * 
 * Return: true if the string is successfully added, false otherwise.
*/
bool	ft_vec_push_str(t_vec *v, const char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	while (v->len + str_len > v->capacity)
	{
		if (ft_vec_resize(v) == false)
			return (false);
	}
	ft_memcpy(v->data + v->len, str, str_len);
	v->len += str_len;
	return (true);
}

/**
 * ft_vec_to_str - Converts the vector to a null-terminated string.
 * @v: The vector to be converted.
 * 
 * This function adds a null terminator to the end of the vector data,
 * allocates a new array to store the null-terminated string, copies the
 * vector data to the new array, and frees the old data array within the
 * vector. If any memory allocation fails, the function returns NULL.
 * 
 * Return: A pointer to the newly allocated null-terminated string, or NULL
 * if memory allocation fails.
*/
char	*ft_vec_to_str(t_vec *v)
{
	char	*tmp;

	if (!ft_vec_push(v, '\0'))
		return (NULL);
	//return (v->data);
	tmp = malloc(sizeof(char) * v->len);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, v->data, v->len);
	//free(v->data);
	ft_vec_free(v);
	//v->data = tmp;
	return (tmp);
}
