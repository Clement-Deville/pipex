/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/19 12:00:29 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	check_access(const char *filename)
{
	if (access(filename, X_OK) == 0)
		return (0);
	else
	{
		perror(filename);
		if (errno == ENOENT)
			return (DONOT_EXIST);
		if (errno == EACCES)
			return (CANT_EXEC);
		else
			return (-1);
	}
}
