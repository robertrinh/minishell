/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:04:24 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/09/02 13:06:21 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define B_MAIN_EXIT		"exit"
# define B_MAIN_CD			"cd"
# define B_MAIN_EXPORT		"export"
# define B_MAIN_UNSET		"unset"

# define B_CHILD_ECHO		"echo"
# define B_CHILD_ENV		"env"
# define B_CHILD_PWD		"pwd"

#endif
