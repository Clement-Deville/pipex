/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:41:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/28 17:48:23 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	check_command_access(const char *path)
{
	if (access(path, R_OK) == 0)
		if (access(path, X_OK) == 0)
			return (0);
	// perror(path);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}

char	**add_dir(char **split_path)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_path[i])
	{
		temp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		if (split_path[i] == NULL)
		{
			split_path[i] = temp;
			ft_free("%s", split_path);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split_path);
}

char	**add_cmd_to_path(char **split_path, const char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_path[i])
	{
		temp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], cmd);
		if (split_path[i] == NULL)
		{
			split_path[i] = temp;
			ft_free("%s", split_path);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split_path);
}

int	check_for_all(char **split_path, char **cmd)
{
	int		i;
	int		access_status;
	char	*access_denied_path;

	i = 0;
	access_denied_path = NULL;
	while (split_path[i])
	{
		access_status = check_command_access(split_path[i]);
		if (access_status == 0)
		{
			free(*cmd);
			*cmd = split_path[i];
			return (0);
		}
		if (access_status == CANT_EXEC)
			access_denied_path = split_path[i];
		i++;
	}
	if (access_denied_path)
		return (check_command_access(access_denied_path));
	else
		return (access_status);
}

int	check_for_path_access(char **cmd, char **envp)
{
	char		**split_path;
	char		*cut;
	const char	*path;

	path = get_path(envp);
	cut = ft_strchr(path, '/');
	// ft_printf("Cut: %s\n", cut);
	// ft_printf("Command: %s\n", *cmd);
	split_path = ft_split(cut, ':');
	if (split_path == NULL)
		return (free(cut), perror("Malloc error"), -1);
	int j = 0;
	// while (split_path[j])
	// {
	// 	ft_printf("%s\n", split_path[j]);
	// 	j++;
	// }
	split_path = add_dir(split_path);
	if (split_path == NULL)
		return (0);
	j = 0;
	// while (split_path[j])
	// {
	// 	ft_printf("%s\n", split_path[j]);
	// 	j++;
	// }
	split_path = add_cmd_to_path(split_path, *cmd);
	if (split_path == NULL)
		return (0);
	j = 0;
	// while (split_path[j])
	// {
	// 	ft_printf("%s\n", split_path[j]);
	// 	j++;
	// }
	ft_free("%s", split_path);
	return (check_for_all(split_path, cmd));
}

int	exec_cmd(const char *path, char *const args[], char *envp[])
{
	if (execve(path, args, envp) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

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
