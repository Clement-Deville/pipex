/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 14:04:28 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	check_command_access(const char *path)
{
	if (access(path, R_OK) == 0)
		if (access(path, X_OK) == 0)
			return (0);
	perror(path);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}
