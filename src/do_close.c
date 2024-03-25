/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:02:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/25 14:03:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	do_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close error");
		return (-1);
	}
	return (0);

}
