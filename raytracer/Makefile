# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/12 10:58:13 by ypringau          #+#    #+#              #
#    Updated: 2014/03/27 16:41:52 by rbrieuc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -O4 -Wextra -Wall -Werror -I./includes -I/usr/X11/include
DEBUG = -g3 -fno-inline -DD_ERRORS_ON
LIB = -I libft/includes
LDFLAGS = -L libft -lft -L/usr/X11/lib -lmlx -lXext -lX11
OBJDIR  = .objs
LISTDIR = srcs
DIRSRC = srcs
NAME = raytracer
SRC = $(DIRSRC)/main.c                                   \
	  $(DIRSRC)/get_color.c                              \
	  $(DIRSRC)/draw.c                                   \
	  $(DIRSRC)/caps.c                                   \
	  $(DIRSRC)/phong.c                                  \
	  $(DIRSRC)/matrix.c                                 \
	  $(DIRSRC)/matrix2.c                                \
	  $(DIRSRC)/shadows.c                                \
	  $(DIRSRC)/draw_utils.c                             \
	  $(DIRSRC)/intersection.c                           \
	  $(DIRSRC)/intersection2.c                          \
	  $(DIRSRC)/parser.c                                 \
	  $(DIRSRC)/parse_cube.c                             \
	  $(DIRSRC)/parse_cone.c                             \
	  $(DIRSRC)/parse_cylinder.c                         \
	  $(DIRSRC)/parse_sphere.c                           \
	  $(DIRSRC)/parse_plane.c                            \
	  $(DIRSRC)/parse_utils.c                            \
	  $(DIRSRC)/parse_camera.c                           \
	  $(DIRSRC)/lights_parser.c                          \
	  $(DIRSRC)/lights_parser_2.c                        \
	  $(DIRSRC)/obj_parser.c                             \
	  $(DIRSRC)/material_parser.c                        \
	  $(DIRSRC)/vector_utils.c                           \
	  $(DIRSRC)/lights.c                                 \
	  $(DIRSRC)/lights_utils.c                           \
	  $(DIRSRC)/normal.c                                 \
	  $(DIRSRC)/draw_calc.c                              \
	  $(DIRSRC)/tools.c                                  \
	  $(DIRSRC)/transf.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

.SILENT:

$(addprefix $(OBJDIR)/, %.o): %.c includes
	$(CC) $(CFLAGS) -o $@ -c $< $(LIB)
	printf '\033[0;32mBuilding C Object $@\n\033[0m' "Building C Object $@"

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	printf '\033[1;31m%s \033[1;35m%s \033[1;31m%s \033[1;33m%s\n\033[0m' \
		"Linking C executable" "$(NAME)" "with" "$(CC)"

lib:
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft $@
	/bin/rm -fr $(OBJDIR)
	printf '\033[1;34m%s\n\033[0m' "Clean project $(NAME)"

debug: CFLAGS += $(DEBUG)
debug: re
	printf '\033[1;31m%s \033[1;35m%s\n\033[0m' "Debug version" "$(DEBUG)"

analyze: CFLAGS += --analyze
analyze: re

every: CFLAGS += -Weverything
every: re
	printf '\033[1;33m%s\n\033[0m' "Good job !"

fclean: clean
	$(MAKE) -C libft $@
	/bin/rm -fr $(NAME)
	printf '\033[1;34m%s\n\033[0m' "Fclean project $(NAME)"

re: fclean all

$(OBJDIR):
	/bin/mkdir $(OBJDIR);            \
	for DIR in $(LISTDIR);           \
	do                               \
		/bin/mkdir $(OBJDIR)/$$DIR;  \
	done                             \

.PHONY: clean fclean re
