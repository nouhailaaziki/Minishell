/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:15:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/11 15:37:53 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	sort_matches(char **matches, size_t count)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(matches[j], matches[j + 1]) > 0)
			{
				temp = matches[j];
				matches[j] = matches[j + 1];
				matches[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

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
size_t arg_index, const char *pwd)
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
	dir = opendir(pwd);
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	matches = malloc(matches_capacity * sizeof(char *));
	if (!matches)
	{
		closedir(dir);
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
				new_matches = malloc(matches_capacity * sizeof(char *));
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
				free(matches);
				matches = new_matches;
			}
			matches[matches_count++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (matches_count == 0)
	{
		free(matches);
		return ;
	}
	sort_matches(matches, matches_count);
	new_argc = na_arrlen(cmd_node->cmd) - 1 + matches_count;
	new_argv = malloc((new_argc + 1) * sizeof(char *));
	if (!new_argv)
	{
		i = 0;
		while (i < matches_count)
		{
			free(matches[i]);
			i++;
		}
		free(matches);
		return ;
	}
	current_pos = 0;
	i = 0;
	while (i < arg_index)
	{
		new_argv[current_pos++] = ft_strdup(cmd_node->cmd[i]);
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
		new_argv[current_pos++] = ft_strdup(cmd_node->cmd[i]);
		i++;
	}
	new_argv[current_pos] = NULL;
	i = 0;
	while (cmd_node->cmd[i])
	{
		free(cmd_node->cmd[i]);
		i++;
	}
	free(cmd_node->cmd);
	cmd_node->cmd = new_argv;
	free(matches);
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;
	int		original_len;

	if (!cmd_node || !cmd_node->cmd)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(stash->pwd_backup);
	if (!pwd)
		return (perror("malloc"));
	i = 0;
	while (cmd_node->cmd[i])
	{
		if (ft_strchr(cmd_node->cmd[i], '*'))
		{
			original_len = na_arrlen(cmd_node->cmd);
			handle_wildcards(cmd_node, cmd_node->cmd[i], i, pwd);
			if (na_arrlen(cmd_node->cmd) != original_len)
			{
				free(pwd);
				pwd = getcwd(NULL, 0);
				if (!pwd)
					pwd = ft_strdup(stash->pwd_backup);
				if (!pwd)
					return (perror("malloc"));
				i = 0;
				continue ;
			}
		}
		i++;
	}
	free(pwd);
	i =0;
	while(cmd_node->cmd[i])
		expand_quotes(&cmd_node->cmd[i++]);

}
