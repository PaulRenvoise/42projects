/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:18:38 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/11 15:29:32 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>

typedef struct		s_read
{
	int				size;
	int				index;
	int				fd;
	char			_pad0[4];
	char			*read;
	struct s_read	*next;
}					t_read;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_btree
{
	void			*data;
	size_t			size;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef struct		s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_llist
{
	size_t			size;
	t_node			*head;
	t_node			*tail;
}					t_llist;

typedef struct	s_quickswap
{
	t_list		*axe;
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*prev;
	t_list		*next;
}				t_quickswap;

typedef struct			s_opts
{
	int					d;
	char				c;
	char				_pad1[3];
	char				*s;
	unsigned int		u;
	unsigned int		o;
	unsigned int		x;
	char				_pad2[4];
	long unsigned int	p;
}						t_opts;

/*
** Memory related functions.
*/

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		*ft_memccpy(void *s1, const void * s2, int c, size_t n);
void		*ft_memmove(void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
void		*ft_realloc(void *ptr, size_t size);

/*
** String related functions.
*/

size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strncpy(char *s1, const char *s2, size_t n);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
size_t		ft_strnchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		**ft_strwsplit(char const *s);
int			*ft_strsplittoi(char const *s, char c);
char		*ft_strrev(const char *s);
char		*ft_revcase(const char *s);
int			get_next_line(int const fd, char **line);
int			ft_printf(const char *format, ...);

/*
** Conversion related functions.
*/

char		*ft_itoa(int n);
char		*ft_uitoa(unsigned int n);
char		*ft_uitooa(unsigned int n);
char		*ft_uitoxa(long int n);
char		*ft_luitoxa(unsigned long n);
int			ft_atoi(const char *str);
float		ft_atof(const char *str);
double		ft_sqrt(double n);
long		ft_abs(long n);
double		ft_dabs(double n);
double		ft_cos(double angle);
double		ft_sin(double angle);


/*
** Caracter related functions.
*/

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/*
** Print related functions.
*/

void		ft_putchar(char c);
void		ft_putstr(char const *s);
void		ft_putendl(char const *s);
void		ft_putnbr(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*
** Simply linked lists functions.
*/

t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstaddend(t_list **alst, t_list *new);
void		ft_lstaddat(t_list **alst, t_list *new, size_t pos);
void		ft_lstnew_or_add(t_list **alst, void *data, size_t size, int call);
void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstclr(t_list **alst);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstsplit(char const *s, char c);
int			ft_lstsize(t_list *alst);
t_list		*ft_lstget(t_list *alst, unsigned int nbr);
void		ft_lstprint(t_list *alst);
t_list		*ft_lstquicksort(t_list *alst, t_list *end);
void		ft_lstswap(t_list *lst1, t_list *lst2);
void		ft_lstbblsort(t_list **alst);

/*
** Doubly linked lists functions.
*/

t_llist		*ft_llstnew(void);
void		ft_llstadd(t_llist **allst, void const *content);
void		ft_llstaddend(t_llist **allst, void const *content);
void		ft_llstaddat(t_llist **allst, void const *content, size_t pos);
void		ft_llstnew_or_add(t_llist **allst, void const *content, int call);
void		ft_llstprint(t_llist *allst);
void		ft_llstdel(t_llist **allst, t_node **node);

/*
** Circular doubly linked lists functions.
*/

t_node		*ft_cllstnew(void);
void		ft_cllstadd(t_node **root, void const *content);
void		ft_cllstaddend(t_node **root, void const *content);
void		ft_cllstaddat(t_node **root, void const *content, size_t pos);
void		ft_cllstnew_or_add(t_node **root, void const *content, int call);
void		ft_cllstdel(t_node *node);
void		ft_cllstclr(t_node *root);
void		ft_cllstprint(t_node *root);

/*
** Binary tree functions.
*/

t_btree		*ft_bnew(void *data, size_t size);
int			ft_badd(t_btree **abtree, void *data, size_t size, int side);
void		ft_bnew_or_add(t_btree **abtree, void *data, size_t size, int side);
void		*ft_bsearch(t_btree *abtree, void *data);
void		ft_bprint(t_btree *abtree);
void		ft_bclr(t_btree **abtree);
#endif
