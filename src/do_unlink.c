/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:21:52 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 10:28:22 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	do_unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
	{
		perror("Erreur lors de la suppression du fichier");
		return (1);
	}
	return (0);
}
