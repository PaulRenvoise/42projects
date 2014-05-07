/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 16:22:22 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/27 19:45:19 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

t_job			*create_job(int pid, char *str)
{
	t_job		*job;

	if (!(job = (t_job *)malloc(sizeof(t_job))))
		print_err("Malloc()", MALLOC);
	job->pid = pid;
	job->str = ft_strdup(str);
	return (job);
}

int				check_if_in_job_list(t_list *list, int pid)
{
	while (list)
	{
		if (((t_job *)(list->content))->pid == pid)
			return (1);
		list = list->next;
	}
	return (0);
}

char			*get_str_job_list(t_list *list, int pid)
{
	while (list)
	{
		if (((t_job *)(list->content))->pid == pid)
			return (((t_job *)(list->content))->str);
		list = list->next;
	}
	return (0);
}

static int		freelist(t_list **list, t_list *tmp)
{
	if ((*list)->next == NULL)
	{
		tmp->next = NULL;
		free(*list);
		return (1);
	}
	else
	{
		tmp->next = (*list)->next;
		free(*list);
		*list = tmp->next;
		return (2);
	}
}

void			del_from_job_list(t_list **list, int pid, int i)
{
	t_list		*head;
	t_list		*tmp;

	tmp = NULL;
	head = *list;
	while (*list)
	{
		if (i == 0 && ((t_job *)((*list)->content))->pid == pid)
		{
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
			return ;
		}
		else if (i != 0 && ((t_job *)((*list)->content))->pid == pid)
		{
			if (freelist(list, tmp) == 1)
				break ;
			continue ;
		}
		tmp = *list;
		*list = (*list)->next;
		i++;
	}
	*list = head;
}
