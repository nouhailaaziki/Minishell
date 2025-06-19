/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:46:52 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/19 19:11:17 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**get_path_list(char **env)
{
	int		i;
	char	*str;
	char	**arr;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			str = na_substr(env[i], 5, ft_strlen(env[i]) - 5);
			arr = na_split(str, ':');
			return (arr);
		}
		i++;
	}
	return (NULL);
}

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

int	is_builtins(char **cmd, t_env **env_list)
{
	int	last_status;

	last_status = 0;
	if (cmd && cmd[0])
	{
		if (!ft_strcmp("exit", cmd[0]))
			run_exit(cmd, last_status);
		else if (!ft_strcmp("env", cmd[0]))
			last_status = env(*env_list);
		else if (!ft_strcmp("pwd", cmd[0]))
			last_status = pwd();
		else if (!ft_strcmp("echo", cmd[0]))
			last_status = echo(cmd);
		else if (!ft_strcmp("cd", cmd[0]))
			last_status = cd(cmd, env_list);
		else if (!ft_strcmp("unset", cmd[0]))
			last_status = unset(env_list, cmd);
		else if (!ft_strcmp("export", cmd[0]))
			last_status = export(cmd, env_list);
		else
			last_status = -1;
	}
	return (last_status);
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "unset") ||
			!ft_strcmp(cmd, "exit"));
}

int	execute_command(char **cmd, t_redir *redirs, t_env **env_list)
{
	char	**path_list;
	char	**envp;
	int		status;

	status = 0;
	if (is_parent_builtin(cmd[0]))
	{
		handle_redirs(redirs);
		return (is_builtins(cmd, env_list));
	}
	pid_t pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (!pid)
	{
		setup_signals_child();
		7889 && (envp = get_env_arr(*env_list), path_list = get_path_list(envp));
		handle_redirs(redirs);
		status = is_builtins(cmd, env_list);
		if (status >= 0)
			exit(status);
		is_it_dir(cmd[0]);
		execcmd(path_list, cmd, envp);
		if ((ft_strchr(cmd[0], '/') || !path_list) && !access(cmd[0], X_OK))
		{
			execve(cmd[0], cmd, envp);
			perror("execve failed");
			exit(1);
		}
		errno_manager(cmd[0]);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
