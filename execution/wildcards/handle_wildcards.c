/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:15:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/08 13:44:55 by noaziki          ###   ########.fr       */
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

void	handle_wildcards(t_tree *cmd_node, const char *pattern, \
size_t arg_index, char *pwd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	size_t			matches_count;
	size_t			matches_capacity;
	char			**new_argv;
	size_t			new_argc;
	size_t			current_pos;
	size_t			i;
	char			**new_matches;

	matches = NULL;
	matches_count = 0;
	matches_capacity = 10;
	new_argv = NULL;
	new_argc = 0;
	dir = opendir(pwd);
	if (!dir)
	{
		perror("opendir");
		free(pwd);
		return ;
	}
	matches = nalloc(matches_capacity * sizeof(char *));
	if (!matches)
	{
		closedir(dir);
		free(pwd);
		return ;
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			if (matches_count >= matches_capacity)
			{
				matches_capacity *= 2;
				new_matches = nalloc(matches_capacity * sizeof(char *));
				if (!new_matches)
				{
					perror("malloc");
					break ;
				}
				i = 0;
				while (i < matches_count)
				{
					new_matches[i] = matches[i];
					i++;
				}
				matches = new_matches;
			}
			matches[matches_count++] = na_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	free(pwd);
	if (matches_count == 0)
		return ;
	new_argc = na_arrlen(cmd_node->cmd) - 1 + matches_count;
	new_argv = nalloc((new_argc + 1) * sizeof(char *));
	if (!new_argv)
		return ;
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
	while (cmd_node->cmd[i])
	{
		new_argv[current_pos++] = na_strdup(cmd_node->cmd[i]);
		i++;
	}
	new_argv[current_pos] = NULL;
	cmd_node->cmd = new_argv;
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;
	int		original_len;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		if (!pwd)
			return (perror("getcwd"));
	if (!cmd_node || !cmd_node->cmd)
	{
		free(pwd);
		return ;
	}
	while (cmd_node->cmd[i])
	{
		if (ft_strchr(cmd_node->cmd[i], '*'))
		{
			original_len = na_arrlen(cmd_node->cmd);
			handle_wildcards(cmd_node, cmd_node->cmd[i], i, pwd);
			if (na_arrlen(cmd_node->cmd) != original_len)
			{
				i = 0;
				pwd = getcwd(NULL, 0);
				if (!pwd)
				{
					pwd = na_strdup(stash->pwd_backup);
					if (!pwd)
					{
						perror("malloc");
						return ;
					}
				}
				continue ;
			}
		}
		i++;
	}
	free(pwd);
}
