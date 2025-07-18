/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:15:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/16 11:57:23 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	process_directory_entries(DIR *dir, const char *pattern,
		t_match_data *data)
{
	struct dirent	*entry;

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
			resize_matches_if_needed(data);
			if (!data->matches)
				break ;
			data->matches[(data->count)++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
}

char	**find_matching_entries(const char *pattern, const char *pwd,
		size_t *matches_count)
{
	DIR				*dir;
	t_match_data	data;

	data.capacity = 10;
	data.matches = malloc(data.capacity * sizeof(char *));
	if (!data.matches)
		return (NULL);
	data.count = 0;
	dir = opendir(pwd);
	if (!dir)
	{
		perror("opendir");
		free(data.matches);
		return (NULL);
	}
	process_directory_entries(dir, pattern, &data);
	closedir(dir);
	*matches_count = data.count;
	return (data.matches);
}

char	**build_new_argv(char **old_argv, char **matches, size_t arg_index,
		size_t matches_count)
{
	char	**new_argv;
	size_t	new_argc;
	size_t	current_pos;
	size_t	i;

	new_argc = na_arrlen(old_argv) - 1 + matches_count;
	new_argv = malloc((new_argc + 1) * sizeof(char *));
	if (!new_argv)
		return (NULL);
	current_pos = 0;
	i = 0;
	while (i < arg_index)
		new_argv[current_pos++] = ft_strdup(old_argv[i++]);
	i = 0;
	while (i < matches_count)
		new_argv[current_pos++] = matches[i++];
	i = arg_index + 1;
	while (old_argv[i])
		new_argv[current_pos++] = ft_strdup(old_argv[i++]);
	new_argv[current_pos] = NULL;
	return (new_argv);
}

void	handle_wildcards(t_tree *cmd_node, const char *pattern,
size_t arg_index, const char *pwd)
{
	char	**matches;
	size_t	matches_count;
	char	**new_argv;
	size_t	i;

	matches = find_matching_entries(pattern, pwd, &matches_count);
	if (!matches || matches_count == 0)
		return (free(matches));
	sort_matches(matches, matches_count);
	new_argv = build_new_argv(cmd_node->cmd, matches, arg_index,
			matches_count);
	if (!new_argv)
	{
		i = 0;
		while (i < matches_count)
			free(matches[i++]);
		return (free(matches));
	}
	cleanup_string_array(cmd_node->cmd);
	cmd_node->cmd = new_argv;
	free(matches);
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;

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
			handle_wildcards(cmd_node, cmd_node->cmd[i], i, pwd);
		i++;
	}
	free(pwd);
}
