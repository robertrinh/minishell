/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:57:57 by qtrinh            #+#    #+#             */
/*   Updated: 2024/08/17 20:54:59 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Counts the occurances of the given delimiter character in the given string
*/
static int	count_delimiters(const char *arg, char delimiter)
{
	int	i;
	int	delimiter_count;

	i = 0;
	delimiter_count = 0;
	while (arg[i])
	{
		if (arg[i] == delimiter)
			delimiter_count++;
		i++;
	}
	return (delimiter_count);
}

/*
	Allows only alphabetical characters in export key
*/
static bool	is_valid_export_key(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPORT_DELIMITER)
			return (true);
		if (ft_isalpha(arg[i]) == false)
			return (false);
		i++;
	}
	return (false);
}

/*
	Does not allow spaces in export value
*/
static bool is_valid_export_value(const char *arg)
{
	int	i;
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPORT_DELIMITER)
			break ;
		i++;
	}
	while (arg[i])
	{
		if (is_white_space(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_export_arg(const char *arg)
{
	if (arg == NULL)
		return (false);
	if (ft_strncmp(arg, "=", 1) == 0)
		return (false);
	if (count_delimiters(arg, EXPORT_DELIMITER) > 1)
		return (false);
	if (is_valid_export_key(arg) == false)
		return (false);
	if (is_valid_export_value(arg) == false)
		return (false);
	return (true);
}
