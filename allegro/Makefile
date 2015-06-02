CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++11 -stdlib=libc++
NAME	= ../allegro.so
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
INCS	= -I incs -I ../incs -I ~/.brew/Cellar/allegro/5.0.11/include/
LIBS	= -L ~/.brew/Cellar/allegro/5.0.11/lib/
SRCS	= $(wildcard $(SDIR)/*.cpp)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) `pkg-config --cflags --libs allegro-5.0 allegro_font-5.0 allegro_main-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR);

$(addprefix $(ODIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)
	printf '%s\n' "Building object for $<"

clean:
	/bin/rm -rf $(ODIR)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) library is cleaned."

fclean:
	/bin/rm -rf $(ODIR)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) library is fcleaned."

re: fclean all

.PHONY: all analyze lib clean fclean re
.SILENT:
