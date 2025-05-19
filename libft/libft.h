/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:38:47 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 11:28:38 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long int	t_ul;
typedef unsigned char		t_uchar;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Printf

# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"
# define BASE_10 "0123456789"
# define POSSIBLE_FLAGS "cspdiuxX%"

int		ft_printf(char *input, ...);
int		ft_nexus(char input, va_list args);
int		ft_putnbr_base(unsigned int nbr, char *base, int total);
int		ft_printchar(char c);
int		ft_printstring(char *str);
int		ft_printint(int n);
int		ft_printuint(unsigned int n);
int		ft_printhexbig(unsigned int n);
int		ft_printhexsmall(unsigned int n);
int		ft_printptr(void *ptr);

// Get Next Line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *str, char *buffer);
int		ft_strlen_gnl(char *s, int flag);

// Strings

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s);
char	*ft_itoa(long int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);

// Checks

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

// Files

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *buf, int fd);
void	ft_putstr_fd(char *buf, int fd);
void	ft_putnbr_fd(int n, int fd);

// Memory
//
// A small explanation of the new optimizations for
// the memcpy and bzero functions:
//
// Normally these are written as (uchar )array[i] = (uchar )x
// so they copy 1 byte at the time
//
// What ive done is first i allign them, make the
// pointer be at a boundary of x bytes
// dependant on system and then i copy
// sizeof(unsigned long int) at a time
// the compiler will then optimize that so that
// it takes as long to copy 4 or 8 bytes
// (dependant on system) as it did to copy 1 previously
//
// the n > 12 is the thresshold at which the extra time
// it takes to call up the functions
// and new instructions is worth it, this was not tested by me of course
// but stolen from the glibc code :)

void	*ft_memset(void	*s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size);

// Lists

// Normal
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **head, t_list *node);
void	ft_lstadd_front(t_list **head, t_list *node);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Doubly linked
t_dlist	*ft_dlistnew(void *content);
t_dlist	*ft_dlistlast(t_dlist *lst);
int		ft_dlistsize(t_dlist *lst);
void	ft_dlistdelone(t_dlist *lst, void (*del)(void *));
void	ft_dlistadd_back(t_dlist **head, t_dlist *node);
void	ft_dlistadd_front(t_dlist **head, t_dlist *node);
void	ft_dlistclear(t_dlist **lst, void (*del)(void *));
void	ft_dlistiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlistmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));

#endif
