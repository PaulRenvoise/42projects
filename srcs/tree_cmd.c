/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 13:56:42 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:43:35 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

static t_item		*create_item(char *name, char *value)
{
	t_item			*item;

	if (!(item = (t_item *)malloc(sizeof(t_item))))
		print_err("Malloc()", MALLOC);
	if (!(item->name = (char *)malloc(sizeof(char) * ft_strlen(name) + 1)))
		print_err("Malloc()", MALLOC);
	ft_memcpy(item->name, name, ft_strlen(name) + 1);
	if (!(item->value = (char *)malloc(sizeof(char) * ft_strlen(value) + 1)))
		print_err("Malloc()", MALLOC);
	ft_memcpy(item->value, value, ft_strlen(value) + 1);
	return (item);
}

static void			look_in_dir(t_termcap *t, DIR *dir)
{
	t_dirent		*dirent;
	t_item			*item;
	char			*str;

	while ((dirent = readdir(dir)) != NULL)
	{
		if ((dirent->d_name)[0] != '.')
		{
			str = ft_strdup(dirent->d_name);
			item = create_item(str, str);
			if (t->completion == NULL)
				t->completion = ft_btree_create();
			ft_btree_insert_node(t->completion, item, &ft_strcmp);
			free(str);
		}
	}
}

void				create_trees_cmd(t_termcap *t, t_env *e)
{
	int				i;
	DIR				*dir;

	i = 0;
	while (e->paths && e->paths[i])
	{
		if (!(dir = opendir(e->paths[i])))
		{
			i++;
			continue ;
		}
		else
			look_in_dir(t, dir);
		closedir(dir);
		i++;
	}
}
