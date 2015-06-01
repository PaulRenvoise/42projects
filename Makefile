CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++11 -stdlib=libc++
CHECK	= -g3 -fno-inline -DD_ERRORS_ON
NAME	= nibbler
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
HDIR	= incs
SFDIR	= ~/.brew/Cellar/sfml/2.2_1/include/
SDDIR	= ~/.brew/Cellar/sdl2/2.0.3/include/
SFLIB	= ~/.brew/Cellar/sfml/2.2_1/lib/
SDLIB	= ~/.brew/Cellar/sdl2/2.0.3/lib/
SRCS	= $(wildcard $(SDIR)/*.cpp)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS) $(HDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L $(SFLIB) -L $(SDLIB) -lSDL2 -lsfml-system -lsfml-window -lsfml-graphics
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR);

$(addprefix $(ODIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HDIR) -I $(SFDIR) -I $(SDDIR)
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

.PHONY: all check analyze lib clean fclean re
.SILENT:
