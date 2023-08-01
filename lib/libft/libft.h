/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:47:13 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/10 18:27:27 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// LIBC FUNCTIONS
int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t num);
void	*ft_calloc(size_t nbr_elmts, size_t size);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
void	*ft_memchr(const void *str, int c, size_t num);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t num);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *str, const char *sub, size_t len);
char	*ft_strrchr(const char *str, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// Aditional Functions
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *str, char sep);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
void	ft_striteri(char *str, void (*f)(unsigned int, char *));
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *str, unsigned int start, size_t len);

// Bonus
int		ft_lstsize(t_list *head);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *head);
void	ft_lstadd_front(t_list **head, t_list *new);
void	ft_lstadd_back(t_list **head, t_list *new);
void	ft_lstdelone(t_list *node, void (*del)(void *));
void	ft_lstclear(t_list **head, void (*del)(void *));
void	ft_lstiter(t_list *head, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif // LIBFT_H
