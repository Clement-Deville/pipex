/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:36 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/08 18:18:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	do_pipe(int pipfd[2])
{
	if (pipe(pipfd) == -1)
	{
		perror("Erreur lors de la creatin du pipe");
		return (1);
	}
	return (0);
}
