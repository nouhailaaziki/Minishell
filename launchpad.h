/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:01:30 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/05 17:38:04 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include "libft/libft.h"

// environment linked list :
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		run_echo(char **argv);
int		run_pwd(t_env **env_list);
int		run_env(t_env **env_list);
int		run_cd(char **argv, t_env **env_list);
void	run_exit(char **argv, int argc, int last_status);
void	executor(char **argv, int argc, t_env **env_list);
void	fill_env_list(char **envp, t_env **env_list);

#endif