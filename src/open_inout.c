/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_inout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:56 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 11:47:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	*open_inout(char *const argv[])
{
	static int	inout[2];

	inout[IN] = open(argv[1], O_RDONLY);
	if (inout[IN] == -1)
	{
		perror("Erreur lors d'open");
		return (NULL);
	}
	inout[OUT] = open(argv[4], O_WRONLY);
	if (inout[OUT] == -1)
	{
		perror("Erreur lors d'open");
		close(inout[IN]);
		return (NULL);
	}
	return (inout);
}
