/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:07:55 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 18:01:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_commands(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args)
	{
		ft_free("%s", cmds[i].args);
		i++;
	}
	free(cmds);
}

// void	free_commands(char ***cmds)
// {
// 	int	i;

// 	i = 0;
// 	while (cmds[i])
// 	{
// 		ft_free("%s", cmds[i]);
// 		i++;
// 	}
// 	free(cmds);
// }
