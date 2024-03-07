/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dupd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:16 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 10:56:39 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Erreur lors de dup2");
		return (1);
	}
	return (0);
}
