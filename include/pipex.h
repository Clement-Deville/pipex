/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:09:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/22 17:58:56 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define NO_FORK -2

# define DONOT_EXIST 127
# define CANT_EXEC 126

# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <get_next_line.h>

typedef struct s_command
{
	char	**args;
	int		status;
	int		pid;
}	t_command;

int		check_command_access(const char *path);
int		exec_cmd(const char *path, char *const args[], char *const envp[]);
int		do_unlink(const char *pathname);
int		do_pipe(int pipfd[2]);
int		do_dup2(int oldfd, int newfd);

void	free_commands(t_command *cmds);
// void	free_commands(char ***cmds);
char	***parse_commands(int argc, char **argv);

// REDIRECTION


int		set_input_here_doc(char *limiter);
int		set_output_append(char *filename, t_command *last_command);
int		set_input(char *filename, t_command *first_command);
int		set_output(char *filename, t_command *first_command);
// int		set_input(char *filename);
// int		set_output(char *filename);

// UTILS

void	print_commands(t_command *cmds);
int		nbr_of_cmds(t_command *cmds);
// int		nbr_of_cmds(char ***cmds);
t_bool	are_in_child_one(int pid1);
t_bool	are_in_child_two(int pid1, int pid2);

//FD UTILS

int		close_parent(int *pipefd, int size);
void	close_useless_fd(int *pipefd, int size);
void	connect_write(int *pipefd);
void	connect_read(int *pipefd);

// WAIT FOR ALL

int		wait_for_all(t_command *cmds, int size, int access_status);
// int		wait_for_all(int *pid_tab, int size, int access_status);

// START PIPING

int		start_piping(t_command *cmds, char *envp[]);
// int		start_piping(char ***cmds, char *envp[]);


#endif
