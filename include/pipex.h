/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:09:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/28 17:32:50 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# define NO_FORK -2

# define CANT_EXEC 126
# define DONOT_EXIST 127

# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_command
{
	char	**args;
	int		status;
	int		pid;
}	t_command;

// commands.c

int				check_for_path_access(char **cmd, char **envp);
char			*get_path(char *envp[]);
int				check_command_access(const char *path);
int				exec_cmd(const char *path, char *const args[], char *envp[]);
void			free_commands(t_command *cmds);

// do.c

int			do_pipe(int pipfd[2]);
int			do_close(int fd);
int			do_dup2(int oldfd, int newfd);
int			do_fork(t_command *cmds, int i, int *pipefd, char *envp[]);

// fd_utils.c

int			connect_read(int *pipefd);
int			connect_write(int *pipefd);
int			close_useless_fd(int *pipefd, int size);
int			close_parent(int *pipefd, int size);

// here_doc.c

int			read_stdin(char *limiter, int *pipefd);
int			connect_here_doc(int pid, int *pipefd);
int			set_input_here_doc(char *limiter);

// parse.c

void		init(t_command *cmds);
t_command	*parse(int argc, char **argv);
void		parse_here_doc(int argc, char *argv[], t_command **cmds);
void		parse_standard(int argc, char *argv[], t_command **cmds);

// redirection.c

int			set_input(char *filename, t_command *first_command);
int			set_output(char *filename, t_command *first_command);
int			set_input_here_doc(char *limiter);
int			set_output_append(char *filename, t_command *last_command);

// start_piping.c

int			start_piping(t_command *cmds, char *envp[]);

// utils.c

t_bool		are_in_child(int pid1);
t_bool		is_cmd_executable(t_command cmds);
int			nbr_of_cmds(t_command *cmds);

#endif
