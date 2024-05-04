/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 19:13:47 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/05/02 15:07:59 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Reallocates memory for a previously allocated block, possibly moving it to a
// new location, and copies the old content to the new location. If necessary, 
// it also allocates new memory or frees up memory.

// Parameters:
//      ptr: A pointer to the previously allocated memory block. 
//				If NULL, behaves like malloc(size).
//      size: The new size of the memory block, in bytes.

// Return Value: 
//      On success, returns a pointer to the reallocated memory block.
//      On failure, returns NULL. In this case, the original block of 
//				memory is left unchanged.

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
