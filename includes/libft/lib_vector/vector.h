/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/15 12:38:45 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/15 15:46:08 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "../includes/libft.h"

typedef struct s_vec {
	char *data;
	unsigned int len;
	unsigned int capacity;
}	t_vec;

// ft_vector.c
void	ft_free_vector(t_vec *v);
bool	ft_vec_init(t_vec *v, unsigned int size);
bool	ft_vec_resize(t_vec *v);
bool	ft_vec_push(t_vec *v, char c);
bool	ft_vec_push_str(t_vec *v, const char *str);
char	*ft_get_str(t_vec *v);

#endif
