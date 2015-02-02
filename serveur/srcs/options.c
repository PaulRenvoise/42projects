/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:31:19 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/11 16:46:44 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

static void	add_max_to_team(t_env *e)
{
	t_list	*head;

	if (e->teams != NULL)
	{
		head = e->teams;
		while (e->teams)
		{
			((t_team *)(e->teams->content))->max = e->max_client;
			e->teams = e->teams->next;
		}
		e->teams = head;
	}
}

static void	create_teams(t_env *e, char **av, int *i)
{
	(*i)++;
	while (av[*i][0] != '-')
	{
		if (e->teams == NULL)
			e->teams = ft_lstnew(new_team(e, av[*i]), sizeof(t_team));
		else
			ft_lstadd_end(&e->teams, ft_lstnew(new_team(e, av[*i]),
					sizeof(t_team)));
		(*i)++;
	}
	*i = *i - 2;
}

static void	check_options(t_env *e, char **av, int *i)
{
	if (av[*i][1] == 'p')
		e->port = ft_atoi(av[*i + 1]);
	else if (av[*i][1] == 'x')
		e->width = ft_atoi(av[*i + 1]);
	else if (av[*i][1] == 'y')
		e->height = ft_atoi(av[*i + 1]);
	else if (av[*i][1] == 'c')
	{
		e->max_client = ft_atoi(av[*i + 1]);
		add_max_to_team(e);
	}
	else if (av[*i][1] == 't')
		e->time = ft_atoi(av[*i + 1]);
	else if (av[*i][1] == 'n')
		create_teams(e, av, i);
	else
		usage(av);
}

void		parse_options(t_env *e, char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			check_options(e, av, &i);
			i++;
		}
		else
			usage(av);
		i++;
	}
}
