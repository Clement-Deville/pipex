/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:07:55 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/22 17:37:07 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_commands(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args)
	{
		ft_putstr_fd(cmds[i].args[0], 2);
		ft_putendl_fd("ok", 2);
		ft_free("%s", cmds[i].args);
		ft_putnbr_fd(i, 2);
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
