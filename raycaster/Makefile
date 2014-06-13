# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/31 17:26:43 by prenvois          #+#    #+#              #
#    Updated: 2014/02/11 18:49:00 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
CHECK = -Weverything -g -O2
NAME = wolf3d
HDIR = includes
MLX = /usr/X11/lib
XLIBDIR = /usr/X11/include/X11
LDIR = libft
LHDIR = libft/includes
SRCS = wolf3d.c raycasting.c utils.c utils2.c utils3.c check_inputs.c \
	   draw.c draw_utils.c
OBJS = $(SRCS:.c=.o)

all: lib $(NAME)

lib:
	$(MAKE) -C $(LDIR)

$(NAME): $(OBJS) $(LDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(MLX) -lmlx -lXext -lX11 -L./$(LDIR) -lft
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

%.o: %.c $(HDIR)
	$(CC) $(CFLAGS) -c $< -I $(LHDIR) -I $(HDIR) -I $(XLIBDIR)
	printf '%s\n' "Building object for $<"

check: CFLAGS = $(CHECK)
check: re

clean:
	$(MAKE) -C $(LDIR) $@
	/bin/rm -rf $(OBJS)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is cleaned."

fclean:
	$(MAKE) -C $(LDIR) $@
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is fcleaned."

re: fclean all

.PHONY: all, clean, fclean, re
.SILENT:
