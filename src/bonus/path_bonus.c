/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:09:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 18:00:34 by cdeville         ###   ########.fr       */
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
	char	**complete_path;

	i = 0;
	complete_path = (char **)malloc(sizeof(char *) * (len(split_path) + 1));
	if (complete_path == NULL)
		return (perror("Malloc error"), NULL);
	complete_path[len(split_path)] = NULL;
	while (split_path[i])
	{
		complete_path[i] = ft_strjoin(split_path[i], cmd);
		if (complete_path[i] == NULL)
			return (ft_free("%s", complete_path), NULL);
		i++;
	}
	return (complete_path);
}

int	change_path(char **cmd, char *new_path)
{
	char	*temp;

	temp = *cmd;
	*cmd = ft_strdup(new_path);
	if (*cmd == NULL)
	{
		*cmd = temp;
		return (perror("Malloc error"), -1);
	}
	return (free(temp), 0);
}

char	**parse_path(char *envp[])
{
	char		**split_path;
	char		*cut;
	const char	*path;

	path = get_path(envp);
	cut = ft_strchr(path, '/');
	split_path = ft_split(cut, ':');
	if (split_path == NULL)
		return (perror("Malloc error"), NULL);
	split_path = add_dir(split_path);
	return (split_path);
}
