/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msagodir <msagodir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:18:07 by msagodir          #+#    #+#             */
/*   Updated: 2014/03/26 18:14:10 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char			*fill_tab(int i, int *len_word, char *str)
{
	int				k;
	char			*ret;

	k = i - *len_word;
	if (str[i + 1] == '\0')
		*len_word += 1;
	ret = ft_strsub(str, (unsigned int)k, (size_t)(*len_word));
	*len_word = 0;
	return (ret);
}

static char			**split_space_n_tab(char *str, int i)
{
	char			**tab;
	int				len_word;
	int				j;

	len_word = 0;
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *)
					* (size_t)(ft_word_count(str) + 1))))
		exit(EXIT_FAILURE);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
				&& str[i + 1] != '\0')
			len_word += 1;
		else if (len_word > 0)
		{
			tab[j] = fill_tab(i, &len_word, str);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

static int			update_av(t_cmd_tree *root, char ***tmp, int index)
{
	root->ac += strtablen(*tmp) + 1;
	if (!(root->av = ft_realloc(root->av, sizeof(char *) * (size_t)(root->ac))))
		exit(EXIT_FAILURE);
	root->av[root->ac - 1] = NULL;
	root->av = tabjoin((root->av), *tmp, index, strtablen(root->av) - 1);
	return (strtablen(*tmp));
}

static int			parse_tmp_cmd(t_cmd_tree *root, int index, int flag_fd,
					char *line)
{
	int				fd;
	char			**tmp;
	char			**tmp_line;
	int				i;

	tmp = (char **)malloc(sizeof(char *));
	tmp[0] = NULL;
	fd = open(".tmp42sh", O_RDONLY);
	if (fd == -1)
		exit(0);
	while (get_next_line(fd, &line, flag_fd) == 1)
	{
		if (flag_fd == 0)
			flag_fd = 1;
		tmp_line = split_space_n_tab(line, 0);
		tmp = tab_add_end(tmp, tmp_line);
		free_strtab(tmp_line);
		free(line);
	}
	close(fd);
	unlink(".tmp42sh");
	i = update_av(root, &tmp, index);
	free(tmp);
	return (i);
}

void				backquotes(t_env *e, t_cmd_tree *root, t_fd *fd)
{
	int				i;
	char			*tmp;
	char			**tab;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * 4);
	if (root->type == SIMPLE && root->av[0])
	{
		while (root->av[i])
		{
			if (ft_strchr(root->av[i], '`'))
			{
				tmp = ft_strsub(root->av[i], 1, ft_strlen(root->av[i]) - 2);
				tab[0] = ft_strdup(e->path_bin);
				tab[1] = ft_strtrim(tmp);
				tab[2] = ft_strdup(".tmp42sh");
				tab[3] = NULL;
				e->av = tab;
				execute_cmd(e->path_bin, e, fd);
				i += parse_tmp_cmd(root, i, 0, NULL);
			}
			else
				i++;
		}
	}
}
