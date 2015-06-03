CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++11 -stdlib=libc++
CHECK	= -g3 -fno-inline -DD_ERRORS_ON
NAME	= nibbler
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
INCS	= -I incs
SRCS	= $(wildcard $(SDIR)/*.cpp)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	$(MAKE) -C sfml
	$(MAKE) -C sdl
	$(MAKE) -C allegro
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR);

$(addprefix $(ODIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)
	printf '%s\n' "Building object for $<"

check: CFLAGS = $(CHECK)
check: re

clean:
	/bin/rm -rf $(ODIR)
	$(MAKE) $@ -C sfml
	$(MAKE) $@ -C sdl
	$(MAKE) $@ -C allegro
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is cleaned."

fclean:
	/bin/rm -rf $(ODIR)
	/bin/rm -rf $(NAME)
	$(MAKE) $@ -C sfml
	$(MAKE) $@ -C sdl
	$(MAKE) $@ -C allegro
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is fcleaned."

re: fclean all

.PHONY: all check analyze lib clean fclean re
.SILENT:
