/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 13:59:10 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:52:31 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <stdlib.h>
#include <signal.h>

static void		print_long(t_env *e)
{
	ft_putstr("You finished the level in ");
	ft_putnbr(e->misc.fmn);
	ft_putstr(" minute(s) and ");
	ft_putnbr((int)e->misc.fsec);
	if (e->misc.reset)
	{
		ft_putstr(" seconds with ");
		ft_putnbr(e->misc.reset);
		if (e->misc.action)
			ft_putstr(" reset(s) ");
		else
			ft_putendl(" reset(s).");
	}
	if (e->misc.action)
	{
		if (e->misc.reset)
			ft_putstr("and ");
		else
			ft_putstr(" seconds with ");
		ft_putnbr(e->misc.action);
		ft_putendl(" action(s).");
	}
	if (!e->misc.reset && !e->misc.action)
		ft_putendl(" seconds.");
}

static void		print_fast(t_env *e)
{
	ft_putstr("You finished the level in ");
	ft_putnbr((int)e->misc.fsec);
	if (e->misc.reset)
	{
		ft_putstr(" seconds with ");
		ft_putnbr(e->misc.reset);
		if (e->misc.action)
			ft_putstr(" reset(s) ");
		else
			ft_putendl(" reset(s).");
	}
	if (e->misc.action)
	{
		if (e->misc.reset)
			ft_putstr("and ");
		else
		ft_putstr(" seconds with ");
		ft_putnbr(e->misc.action);
		ft_putendl(" action(s).");
	}
	if (!e->misc.reset && !e->misc.action)
		ft_putendl("seconds.");
}

void			display_score(t_env *e)
{
	gettimeofday(&e->misc.score, NULL);
	e->misc.esec = e->misc.score.tv_sec;
	e->misc.fsec = (e->misc.esec - e->misc.ssec);
	if (e->misc.fsec > 60)
	{
		e->misc.fmn = (e->misc.fsec - (e->misc.fsec % 60)) / 60;
		e->misc.fsec %= 60;
		print_long(e);
	}
	else
		print_fast(e);
	if (e->misc.c == 42)
		ft_putendl("Bonus point for finding that secret !");
	else if (e->misc.esec - e->misc.ssec < 30)
		ft_putendl("Perfect !");
	else if (e->misc.esec - e->misc.ssec < 60)
		ft_putendl("Nice one !");
	else if (e->misc.esec - e->misc.ssec < 140)
		ft_putendl("Not bad.");
	else if (e->misc.esec - e->misc.ssec < 300)
		ft_putendl("You can do better...");
	else if (e->misc.esec - e->misc.ssec > 300)
		ft_putendl_fd("Maybe you need a map ?", 2);
	kill(g_pidfather, SIGTERM);
	exit(EXIT_SUCCESS);
}

static void		check_triggers2(t_env *e)
{
	if ((e->v.posy > 2 && e->v.posy < 3) && (e->v.posx > 2 && e->v.posx < 3))
		e->map[2][1] = 3;
	if ((e->v.posy > 9 && e->v.posy < 10) && (e->v.posx > 2 && e->v.posx < 4))
		e->map[2][8] = 3;
	if ((e->v.posy > 10 && e->v.posy < 11) && (e->v.posx > 2 && e->v.posx < 3))
		e->map[3][9] = 0;
	if ((e->v.posy > 9 && e->v.posy < 10) && (e->v.posx > 3 && e->v.posx < 4))
		e->map[5][11] = 0;
	if ((e->v.posy > 3 && e->v.posy < 4)
		&& (e->v.posx > 15.9 && e->v.posx < 16))
		display_score(e);
}

void			check_triggers(t_env *e)
{
	static int	call = 0;

	if ((e->v.posy > 3 && e->v.posy < 5) && (e->v.posx > 9 && e->v.posx < 10)
			&& e->misc.c != 42)
	{
		e->v.posx = 1.7;
		e->v.posy = 3.5;
		e->misc.c++;
	}
	if ((e->v.posy > 1 && e->v.posy < 2) && (e->v.posx > 20 && e->v.posx < 21))
	{
		e->v.posx = 11;
		e->v.posy = 3.5;
	}
	if ((e->v.posy != 3.5 || e->v.posx != 1.7) || (e->v.dirx != -1))
	{
		if (!call)
		{
			gettimeofday(&e->misc.score, NULL);
			e->misc.ssec = e->misc.score.tv_sec;
			call = 1;
		}
		e->map[0][3] = 5;
	}
	check_triggers2(e);
}
