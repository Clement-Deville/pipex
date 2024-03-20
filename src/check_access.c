/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/20 10:08:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	check_access(const char *filename)
{
	if (access(filename, R_OK) == 0)
		if (access(filename, X_OK) == 0)
			return (0);
	perror(filename);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}
