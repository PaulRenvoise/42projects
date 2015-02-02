/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:32:24 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:35:34 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

static void			create_path(char **search, char **path)
{
	int				i;
	int				last;

	last = 0;
	i = 0;
	if (*search && ft_strchr(*search, '/'))
	{
		while ((*search)[i])
		{
			if ((*search)[i] == '/')
				last = i;
			i++;
		}
		if (last == 0)
			*path = ft_strdup("/");
		else
			*path = ft_strsub(*search, 0, (size_t)last);
		*search = ft_strdup(ft_strrchr(*search, '/') + 1);
	}
	else
		*path = ft_strdup(".");
}

static void			add_in_list_cmpl(char *search, char *str, t_termcap *t)
{
	if (search && search[0] == '.')
	{
		if (ft_strncmp(str, search, ft_strlen(search)) == 0)
			add_or_create_dllist(&(t->list_cmpl), ft_strdup(str),
								(int)ft_strlen(str) + 1);
	}
	else
	{
		if ((search == NULL || (ft_strncmp(str, search,
							ft_strlen(search)) == 0)) && str[0] != '.')
			add_or_create_dllist(&(t->list_cmpl), ft_strdup(str),
								(int)ft_strlen(str) + 1);
	}
}

void				create_list_completion(t_termcap *t, char *search)
{
	DIR				*dir;
	t_dirent		*dirent;
	char			*str;
	char			*path;

	create_path(&search, &path);
	dir = opendir(path);
	if (dir == NULL)
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		str = ft_strdup(dirent->d_name);
		if (ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0)
			continue ;
		add_in_list_cmpl(search, str, t);
		if (str)
			free(str);
	}
	if (path)
		free(path);
	closedir(dir);
}
