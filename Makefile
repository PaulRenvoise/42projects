# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 11:37:56 by prenvois          #+#    #+#              #
#    Updated: 2015/06/18 12:49:11 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
CHECK	= -Weverything -g3 -fno-inline -DD_ERRORS_ON
NAME	= libft.a
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
INCS	= -I ./incs
SRCS	= $(wildcard $(SDIR)/*.c)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR)

$(addprefix $(ODIR)/, %.o): %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)
	printf '%s\n' "Building object for $<"

check: CFLAGS = $(CHECK)
check: re

clean:
	/bin/rm -rf $(ODIR)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is cleaned."

fclean:
	/bin/rm -rf $(ODIR)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is fcleaned."

re: fclean all

.PHONY: all check clean fclean re
.SILENT:
