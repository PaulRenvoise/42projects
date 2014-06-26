# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/12 10:58:13 by ypringau          #+#    #+#              #
#    Updated: 2014/06/23 15:33:04 by rbrieuc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash
UNAME = $(shell uname -s)
CC = clang
CFLAGS = -Wextra -Wall -Werror -I./includes
DEBUG = -g3 -fno-inline -DD_ERRORS_ON
LIB = -I libft/includes
LDFLAGS = -L libft -lft
OBJDIR  = .objs
LISTDIR = srcs
DIRSRC = srcs
NAME = serveur
SRC = $(DIRSRC)/main.c                          \
	  $(DIRSRC)/tools.c                         \
	  $(DIRSRC)/read.c                          \
	  $(DIRSRC)/life.c                          \
	  $(DIRSRC)/write.c                         \
	  $(DIRSRC)/fork.c                          \
	  $(DIRSRC)/graphic.c                       \
	  $(DIRSRC)/broadcast_case.c                \
	  $(DIRSRC)/broadcast_case2.c               \
	  $(DIRSRC)/get_k.c                         \
	  $(DIRSRC)/options.c                       \
	  $(DIRSRC)/delete.c                        \
	  $(DIRSRC)/send_map.c                      \
	  $(DIRSRC)/welcome_gfx.c                   \
	  $(DIRSRC)/server.c                        \
	  $(DIRSRC)/take_put.c                      \
	  $(DIRSRC)/eggs.c                          \
	  $(DIRSRC)/new_struct.c                    \
	  $(DIRSRC)/see_pos.c                       \
	  $(DIRSRC)/player.c                        \
	  $(DIRSRC)/get_player.c                    \
	  $(DIRSRC)/see.c                           \
	  $(DIRSRC)/eject.c                         \
	  $(DIRSRC)/inventory.c                     \
	  $(DIRSRC)/action.c                        \
	  $(DIRSRC)/move.c                          \
	  $(DIRSRC)/broadcast.c                     \
	  $(DIRSRC)/inc_lvl_1_5.c                   \
	  $(DIRSRC)/inc_lvl_6_7.c                   \
	  $(DIRSRC)/display.c                       \
	  $(DIRSRC)/incantation.c                   \
	  $(DIRSRC)/check_fd.c                      \
	  $(DIRSRC)/init.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


all: lib $(NAME)

lib:
	$(MAKE) -C libft

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
ifeq ($(UNAME), Darwin)
	printf '\033[1;31m%s \033[1;35m%s \033[1;31m%s \033[1;33m%s\n\033[0m' \
		"Linking C executable" "$(NAME)" "with" "$(CC)"
else
	echo -e '\033[1;31m%s \033[1;35m%s \033[1;31m%s \033[1;33m%s\n\033[0m' \
		"Linking C executable" "$(NAME)" "with" "$(CC)"
endif

$(addprefix $(OBJDIR)/, %.o): %.c includes
	$(CC) $(CFLAGS) -o $@ -c $< $(LIB)
ifeq ($(UNAME), Darwin)
	printf '\033[0;32mBuilding C Object $@\n\033[0m' "Building C Object $@"
else
	echo -e '\033[0;32mBuilding C Object $@\n\033[0m' "Building C Object $@"
endif

$(OBJDIR):
	/bin/mkdir $(OBJDIR);            \
	for DIR in $(LISTDIR);           \
	do                               \
		/bin/mkdir $(OBJDIR)/$$DIR;  \
	done

clean:
	$(MAKE) -C libft $@
	/bin/rm -rf $(OBJDIR)
ifeq ($(UNAME), Darwin)
	printf '\033[1;34m%s\n\033[0m' "Clean project $(NAME)"
else
	echo -e '\033[1;34m%s\n\033[0m' "Clean project $(NAME)"
endif

fclean:
	$(MAKE) -C libft $@
	/bin/rm -rf $(OBJDIR)
	/bin/rm -rf $(NAME)
ifeq ($(UNAME), Darwin)
	printf '\033[1;34m%s\n\033[0m' "Fclean project $(NAME)"
else
	echo -e '\033[1;34m%s\n\033[0m' "Fclean project $(NAME)"
endif

test: CFLAGS = -Wall
test: re

debug: CFLAGS += $(DEBUG)
debug: re
ifeq ($(UNAME), Darwin)
	printf '\033[1;31m%s \033[1;35m%s\n\033[0m' "Debug version" "$(DEBUG)"
else
	echo -e '\033[1;31m%s \033[1;35m%s\n\033[0m' "Debug version" "$(DEBUG)"
endif

analyze: CFLAGS += --analyze
analyze: re

every: CFLAGS += -Weverything
every: re
ifeq ($(UNAME), Darwin)
	printf '\033[1;33m%s\n\033[0m' "Good job !"
else
	echo -e '\033[1;33m%s\n\033[0m' "Good job !"
endif

re: fclean all

.PHONY: all lib clean fclean test debug analyze every re
.SILENT:
