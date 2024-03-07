/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:41 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 16:58:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	check_access(const char *filename)
{
	if (access(filename, R_OK) == 0)
	{
		ft_printf("You have access to \"%s\".", filename);
		return (0);
	}
	else
	{
		perror("Can't open this file");
		return (1);
	}
}
