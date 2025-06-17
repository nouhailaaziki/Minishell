/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:48:15 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/16 11:04:58 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define RESET "\e[0m"
# define SUCCESS 1
# define FAIL 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifdef __APPLE__
#  define FT_OPEN_MAX OPEN_MAX
# endif
# ifdef __MINGW__
#  define FT_OPEN_MAX OPEN_MAX
# endif
# ifdef __MINGW32_MAJOR_VERSION
#  define FT_OPEN_MAX OPEN_MAX
# endif
# ifdef __linux__
#  include <stdio.h>
#  define FT_OPEN_MAX FOPEN_MAX
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_count_words(char *str, char delimiter);
long	ft_atoi_modified(const char *str);
double	ft_pow(double num, double power);
int		*ft_super_strlen(char **array);
int		ft_is_duplicated(char **str);
int		*ft_factors_count(int num);
int		ft_is_int_array(char **s);
int		ft_str_isspace(char *str);
int		ft_is_sorted(char **str);
int		ft_is_uint(char *str);
int		ft_is_int(char *str);
int		ft_isspace(int c);
int		ft_abs(int num);

char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);

void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int c, int fd);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_itoa(int n);
#endif
