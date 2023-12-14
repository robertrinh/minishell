/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/21 11:15:43 by qtrinh        #+#    #+#                 */
/*   Updated: 2023/03/15 16:07:21 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *stash)
{
	int		bytes_read;
	char	temp_string[BUFFER_SIZE + 1];

	bytes_read = 1;
	if (!stash)
		stash = gnl_strdup("");
	if (!stash)
		return (NULL);
	while (spot_new_line(stash) == -1 && bytes_read != 0)
	{
		bytes_read = read(fd, temp_string, BUFFER_SIZE);
		if (bytes_read == -1)
			return (gnl_free(stash));
		temp_string[bytes_read] = '\0';
		stash = gnl_strjoin(stash, temp_string);
		if (!stash)
			return (NULL);
	}
	if (stash[0] == '\0')
		return (gnl_free(stash));
	return (stash);
}

static char	*retrieve_line(char *str)
{
	char	*new_line;
	int		len;

	new_line = NULL;
	len = spot_new_line(str);
	if (len == -1)
		return (str);
	str[len + 1] = '\0';
	new_line = gnl_strdup(str);
	free(str);
	return (new_line);
}

static char	*remainder_line(char *str)
{
	char	*new_string;
	int		len;

	new_string = NULL;
	len = spot_new_line(str);
	if (len == -1)
		return (gnl_free(str), NULL);
	new_string = gnl_strdup(&str[len + 1]);
	free (str);
	return (new_string);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = gnl_strdup(stash);
	stash = remainder_line(stash);
	line = retrieve_line(line);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (line);
}
