# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/12 10:58:13 by ypringau          #+#    #+#              #
#    Updated: 2014/03/27 14:40:01 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash
UNAME = $(shell uname -s)
CC = clang
CFLAGS = -Wextra -Wall -Werror -I./includes
DEBUG = -g3 -fno-inline -DD_ERRORS_ON
LIB = -I libft/includes
LDFLAGS = -L libft -lft -L /usr/lib -ltermcap
OBJDIR  = .objs
LISTDIR = srcs
DIRSRC = srcs
NAME = 42sh
SRC = $(DIRSRC)/analyze.c                         \
	  $(DIRSRC)/auto_completion.c                 \
	  $(DIRSRC)/backquotes.c                      \
	  $(DIRSRC)/builtin_cd.c                      \
	  $(DIRSRC)/builtin_echo.c                    \
	  $(DIRSRC)/builtin_env.c                     \
	  $(DIRSRC)/builtin_exit.c                    \
	  $(DIRSRC)/builtin_fg.c                      \
	  $(DIRSRC)/builtin_history.c                 \
	  $(DIRSRC)/builtin_history_options.c         \
	  $(DIRSRC)/builtin_jobs.c                    \
	  $(DIRSRC)/builtin_jobs_utils.c              \
	  $(DIRSRC)/builtin_setenv.c                  \
	  $(DIRSRC)/builtin_unsetenv.c                \
	  $(DIRSRC)/check_builtin_or_cmd.c            \
	  $(DIRSRC)/exec_all.c                        \
	  $(DIRSRC)/execute_cmd.c                     \
	  $(DIRSRC)/errors.c                          \
	  $(DIRSRC)/free.c                            \
	  $(DIRSRC)/ft_btree.c                        \
	  $(DIRSRC)/ft_btree_insert_node.c            \
	  $(DIRSRC)/ft_btree_insert_node_case.c       \
	  $(DIRSRC)/ft_btree_insert_node_utils.c      \
	  $(DIRSRC)/init.c                            \
	  $(DIRSRC)/lexer.c                           \
	  $(DIRSRC)/lexer_utils.c                     \
	  $(DIRSRC)/list_completion.c                 \
	  $(DIRSRC)/main.c                            \
	  $(DIRSRC)/misc.c                            \
	  $(DIRSRC)/parser.c                          \
	  $(DIRSRC)/parser_redirect.c                 \
	  $(DIRSRC)/parser_utils.c                    \
	  $(DIRSRC)/red_in.c                          \
	  $(DIRSRC)/red_out.c                         \
	  $(DIRSRC)/seek.c                            \
	  $(DIRSRC)/signals.c                         \
	  $(DIRSRC)/static.c                          \
	  $(DIRSRC)/term.c                            \
	  $(DIRSRC)/termcap.c                         \
	  $(DIRSRC)/termcap_alt.c                     \
	  $(DIRSRC)/termcap_delete.c                  \
	  $(DIRSRC)/termcap_key.c                     \
	  $(DIRSRC)/termcap_other.c                   \
	  $(DIRSRC)/termcap_shift.c                   \
	  $(DIRSRC)/termcap_utils.c                   \
	  $(DIRSRC)/tests.c                           \
	  $(DIRSRC)/tree_cmd.c                        \
	  $(DIRSRC)/utils.c                           \
	  $(DIRSRC)/write.c                           \
	  $(DIRSRC)/tab_manipulation.c
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
