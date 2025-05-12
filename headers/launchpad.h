/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:01:30 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 16:38:09 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include "pixie.h"

// environment linked list :
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//  Implement built-in commands functions
int		run_echo(char **argv);
int		run_pwd(t_env **env_list);
int		run_env(t_env **env_list);
int		run_cd(char **argv, t_env **env_list);
int		run_unset(t_env **env_list, char **argv);
int		run_export(int argc, char **argv, t_env **env_list);
int		check_validity(char	*argv, char *cmd);
long	parse_number_or_exit(const char *str, t_env **env_list);
void	run_exit(char **argv, int argc, int last_status, t_env **env_list);
void	executor(char **argv, int argc, t_env **env_list);
void	fill_env_list(char **envp, t_env **env_list);
void	sort_env_list(t_env **env_list);
void	handle_argument(t_env **env_list, char *argv);
void	add_value(t_env	**env_list, char *argv, char *key);
void	update_env(t_env **env_list, char *argv, char *key, int start);
t_env	*create_node(char *argv, size_t key_len, char *sign);

// events
void	free_env_list(t_env **env);

#endif