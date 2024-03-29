/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:36:44 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/02/29 13:30:44 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"

// Definitions of variables
const char* error_messages[] = {
    "ERROR unmatched quote",
	"ERROR unmatched pipe",
	"ERROR unmatched redirect",
    "ERROR malloc failure"
};

const char* color_codes[] = {
    "\x1B[31m",  // RED
    "\x1B[32m",  // GREEN
    "\x1B[33m",  // YELLOW
    "\x1B[34m"   // BLUE
};

const char* RESET_COLOR = "\x1B[0m";

//!global variables not allowed! should change this