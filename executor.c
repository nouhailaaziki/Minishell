/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:33:01 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

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

void	execone(char **cmd, t_env *env_list)
{
	pid_t	pid;
	char	**path_list;
	char	**envp;

	pid = fork();
	if (pid == -1)
		return (perror ("fork failed"));
	7889 && (envp = get_env_arr(env_list), path_list = get_path_list(envp));
	if (!pid)
	{
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
	wait(0);
}

void	execute_command(char **cmd, t_redir *redirs, t_env **env_list)
{
	int	last_status;

	last_status = 0;
	(void)redirs;
	if (!cmd || !cmd[0])
		return ;
	if (cmd[0])
	{
		if (!ft_strcmp("env", cmd[0]))
			env(*env_list);
		else if (!ft_strcmp("pwd", cmd[0]))
			pwd();
		else if (!ft_strcmp("echo", cmd[0]))
			echo(cmd);
		else if (!ft_strcmp("cd", cmd[0]))
			cd(cmd, env_list);
		else if (!ft_strcmp("unset", cmd[0]))
			unset(env_list, cmd);
		else if (!ft_strcmp("export", cmd[0]))
			export(cmd, env_list);
		else if (!ft_strcmp("exit", cmd[0]))
			run_exit(cmd, last_status);
		else
			execone(cmd, *env_list);
	}
}

void	executor(t_tree *ast, t_env **env)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
		execute_command(ast->cmd, ast->redirs, env);
	// else if (ast->type == NODE_PIPE)
	// 	execute_pipe(ast, env);
	// else if (ast->type == NODE_AND)
	// 	execute_and(ast, env);
	// else if (ast->type == NODE_OR)
	// 	execute_or(ast, env);
}
