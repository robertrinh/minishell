/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vector.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/15 12:37:13 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 18:48:46 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * ft_free_vector - Frees the memory allocated for the vector.
 * @v: The vector to be freed.
*/
void	ft_free_vector(t_vec *v)
{
	if (v)
	{
		if (v->data)
		{
			free(v->data);
			v->data = NULL;
		}
		// free(v);
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
	char *tmp;

	tmp = malloc(sizeof(char) * (v->capacity * 2));
	if (!tmp) 
		return (false);
	ft_memcpy(tmp, v->data,  v->len);
	free(v->data);
	v->data = tmp;
	v->capacity *= 2;
	return (true);
}

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
bool ft_vec_push_str(t_vec *v, const char *str)
{
    size_t	str_len; 
	
	str_len = strlen(str);
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
	tmp = malloc(sizeof(char) * v->len);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, v->data, v->len);
	free(v->data);
	v->data = tmp;
	return (tmp);
}
