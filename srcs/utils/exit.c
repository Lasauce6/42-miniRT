/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:16:36 by jili              #+#    #+#             */
/*   Updated: 2025/11/07 15:16:43 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	message_error(char *format, char *detail, int exit_no)
{
	if (!detail)
		printf(format, STR_PROG_NAME);
	else
		printf(format, STR_PROG_NAME, detail);
	return (exit_no);
}

int	error_failure(char *format, char *detail, t_data *data)
{
	free_table(data);
	exit(message_error(format, detail, EXIT_FAILURE));
}
