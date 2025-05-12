/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixie.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:16:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 12:44:58 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXIE_H
# define PIXIE_H

# include <unistd.h>
# include <stdlib.h>

int			ft_isdigit(int c);
int			ft_strcmp(char *s1, char *s2);
int			is_all_char(const char *str, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strndup(const char *s, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);

#endif