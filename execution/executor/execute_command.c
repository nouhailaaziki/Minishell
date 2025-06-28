/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:46:52 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 11:35:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	execcmd(char **path_list, char **cmd, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (path_list && path_list[i])
	{
		path = na_strjoin(path_list[i], "/");
		path = na_strjoin(path, cmd[0]);
		if (!access(path, X_OK))
		{
			execve(path, cmd, envp);
			perror("execve failed");
			exit(1);
		}
		free(path);
		i++;
	}
}

void	run_and_handle_errors(char **path_list, char **cmd, char **envp)
{
	handle_special_cases(path_list, cmd);
	execcmd(path_list, cmd, envp);
	if ((ft_strchr(cmd[0], '/') || !path_list) && !access(cmd[0], X_OK))
	{
		execve(cmd[0], cmd, envp);
		perror("execve failed");
		exit(1);
	}
	if (ft_strchr(cmd[0], '/') || !path_list
		|| !path_list[0] || !ft_strcmp(path_list[0], ""))
		errno_manager(cmd[0]);
	ft_putstr_fd("L33tShell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	child_process_handler(char **cmd, t_redir *redirs, \
t_env **env_list, t_stash *stash)
{
	char	**envp;
	char	**path_list;
	int		stats;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = get_env_arr(*env_list);
	path_list = get_path_list(envp);
	handle_redirs(redirs);
	stats = run_builtins(cmd, env_list, stash->status, stash);
	if (stats >= 0)
		exit(stats);
	run_and_handle_errors(path_list, cmd, envp);
}

int	execute_command(char **cmd, t_redir *redirs, \
t_env **env_list, t_stash *stash)
{
	pid_t	pid;
	int		status;

	if (cmd && is_parent_builtin(cmd[0]))
	{
		handle_redirs(redirs);
		return (run_builtins(cmd, env_list, stash->status, stash));
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (pid == 0)
		child_process_handler(cmd, redirs, env_list, stash);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (WEXITSTATUS(status));
}
