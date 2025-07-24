/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:35:45 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/24 11:47:34 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

size_t	process_unquoted_wildcard(char ***cmd, size_t i, char *pwd)
{
	char	**matches;
	size_t	matches_count;
	size_t	expansion_count;

	matches = prepare_and_find_matches((*cmd)[i], pwd, &matches_count);
	if (!matches)
		return (0);
	if (matches_count > 0)
	{
		expansion_count = handle_matches_found(cmd, matches,
				matches_count, i);
	}
	else
	{
		free(matches);
		expansion_count = resolve_wildcard_entries(cmd, i);
	}
	return (expansion_count);
}

size_t	resolve_wildcard_entries(char ***cmd, size_t i)
{
	char	*literal_arg;
	char	*temp_match[2];
	char	**new_argv;

	literal_arg = remove_quotes((*cmd)[i]);
	if (!literal_arg)
		return (perror("malloc"), 0);
	temp_match[0] = literal_arg;
	temp_match[1] = NULL;
	new_argv = build_new_argv(*cmd, temp_match, i, 1);
	if (!new_argv)
	{
		perror("malloc");
		free(literal_arg);
		return (0);
	}
	cleanup_string_array(*cmd);
	*cmd = new_argv;
	free(literal_arg);
	return (1);
}

char	*get_working_directory(t_stash *stash, char **cmd)
{
	char	*pwd;

	if (!cmd)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(stash->pwd_backup);
	if (!pwd)
		perror("malloc");
	return (pwd);
}

void	check_for_wildcards(char ***cmd, t_stash *stash)
{
	size_t	i;
	size_t	len;
	char	*pwd;
	size_t	increment;

	pwd = get_working_directory(stash, *cmd);
	if (!pwd)
		return ;
	7889 && (i = 0, increment = 1);
	len = (size_t)na_arrlen(*cmd);
	while (i < len && (*cmd)[i])
	{
		if (contains_unquoted_wildcard((*cmd)[i]) == true)
		{
			increment = process_unquoted_wildcard(cmd, i, pwd);
			if (increment == 0)
				break ;
			len = na_arrlen(*cmd);
		}
		else
			expand_quotes(&(*cmd)[i]);
		i += increment;
	}
	free(pwd);
}
