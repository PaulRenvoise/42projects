# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/07 16:54:39 by prenvois          #+#    #+#              #
#    Updated: 2013/12/22 17:35:46 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fdf
HDIR = includes/
LDIR = libft
LHDIR = libft/includes
OBJS = $(SRCS:.c=.o)
SRCS = main.c fdf.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) -L/usr/X11/lib -lmlx -lXext -lX11\
		-L./$(LDIR) -lft

%.o: %.c
	$(MAKE) -C $(LDIR)
	$(CC) $(CFLAGS) -c $< -I $(LHDIR) -I $(HDIR)

clean:
	$(MAKE) -C $(LDIR) $@
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LDIR) $@
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
