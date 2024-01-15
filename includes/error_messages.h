/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:04:35 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/01/15 20:36:29 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

// Errors
typedef enum {
    ERROR_UNMATCHED_QUOTE
} e_error_messages;


// Colors
typedef enum {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    NUM_COLORS
} e_message_colors;


// Variables
extern const char* error_messages[];
extern const char* color_codes[];
extern const char* RESET_COLOR;

#endif
