/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:04:35 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/28 12:18:47 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

// Errors
typedef enum e_error_messages
{
	ERROR_UNMATCHED_QUOTE,
	ERROR_UNMATCHED_PIPE,
	ERROR_UNMATCHED_REDIRECT,
	ERROR_MALLOC,
	ERROR_OPENING_FILE
}	t_error_messages;

// Colors
typedef enum e_message_colors
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	NUM_COLORS
}	t_message_colors;

// Variables
extern const char *error_messages[];
extern const char *color_codes[];
extern const char *RESET_COLOR;
//! global variable -> not allowed. need to change

#endif
