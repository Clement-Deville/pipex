/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:33:22 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 10:13:20 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	exec_cmd(const char *path, char *const args[])
{
	if (execv(path, args) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}
