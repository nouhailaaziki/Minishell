/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:15:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/08 10:42:07 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

size_t	match_pattern(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*string)
			{
				if (match_pattern(pattern, string))
					return (1);
				string++;
			}
			return (0);
		}
		else if (*pattern == *string)
		{
			pattern++;
			string++;
		}
		else
			return (0);
	}
	return (*string == '\0');
}

void	handle_wildcards(t_tree *cmd_node, \
const char *pattern, size_t arg_index, char *pwd)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			matches_capacity;
	char			**matches;
	size_t			matches_count;
	char			**new_matches;
	size_t			new_argc;
	char			**new_argv;
	size_t			current_pos;
	size_t			i;

	dir = opendir(pwd);
	if (!dir)
	{
		perror("opendir");
		free(pwd);
		return ;
	}
	matches_capacity = 10;
	matches = nalloc(matches_capacity * sizeof(char *));
	if (!matches)
	{
		closedir(dir);
		free(pwd);
		return (perror("malloc"));
	}
	matches_count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			if (matches_count >= matches_capacity)
			{
				matches_capacity *= 2;
				new_matches = nalloc(matches_capacity * sizeof(char *));
				if (!new_matches)
				{
					perror("malloc");
					closedir(dir);
					free(pwd);
					return ;
				}
				matches = new_matches;
			}
			matches[matches_count++] = na_strdup(entry->d_name);
		}
	}
	closedir(dir);
	free(pwd);
	if (matches_count == 0)
		return ;
	new_argc = cmd_node->argc - 1 + matches_count;
	new_argv = nalloc((new_argc + 1) * sizeof(char *));
	if (!new_argv)
		return (perror("malloc"));
	current_pos = 0;
	i = 0;
	while (i < arg_index)
	{
		new_argv[current_pos++] = na_strdup(cmd_node->cmd[i]);
		i++;
	}
	i = 0;
	while (i < matches_count)
	{
		new_argv[current_pos++] = matches[i];
		i++;
	}
	i = arg_index + 1;
	while (i < cmd_node->argc)
	{
		new_argv[current_pos++] = na_strdup(cmd_node->cmd[i]);
		i++;
	}
	cmd_node->cmd = new_argv;
	cmd_node->argc = new_argc;
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	size_t	original_argc;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = na_strdup(stash->pwd_backup);
		if (!pwd)
			return (perror("malloc"));
	}
	if (!cmd_node || !cmd_node->cmd)
		return ;
	while (cmd_node->cmd[i])
	{
		if (ft_strchr(cmd_node->cmd[i], '*'))
		{
			original_argc = cmd_node->argc;
			handle_wildcards(cmd_node, cmd_node->cmd[i], i, pwd);
			if (cmd_node->argc != original_argc)
				i = -1;
		}
		i++;
	}
}
