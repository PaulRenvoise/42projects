/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 17:34:46 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/11 16:24:05 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

void			srv_accept(t_env *e, t_net *net, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	(void)e;
	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
		printf("ACCEPT ERROR : can't handle new connection");
	else
	{
		printf("New client #%d from %s:%d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
		dprintf(cs, "BIENVENUE\n");
		net->fds[cs].type = FD_CLIENT;
		net->fds[cs].fct_read = client_read;
		net->fds[cs].fct_write = client_write;
	}
}

void			srv_create(t_net *net, int port)
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;

	pe = (struct protoent*)getprotobyname("tcp");
	if ((s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		error("socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		error("bind");
	if (listen(s, 42) == -1)
		error("listen");
	net->fds[s].type = FD_SERV;
	net->fds[s].fct_read = srv_accept;
}
