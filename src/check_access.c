/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/06 14:11:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	check_access(const char *filename)
{
	if (access(filename, R_OK) == 0)
		ft_printf("You have access to %s.", filename);
	else
	{
		perror("Can't open this file");
		exit (EXIT_FAILURE);
	}
}
