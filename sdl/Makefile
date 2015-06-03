CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++11 -stdlib=libc++
NAME	= ../sdl.so
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
INCS	= -I incs -I ../incs -I ~/.brew/Cellar/sdl2/2.0.3/include/SDL2/ -I ~/.brew/Cellar/sdl2_ttf/2.0.12/include/SDL2/
LIBS	= -L ~/.brew/Cellar/sdl2/2.0.3/lib/ -L ~/.brew/Cellar/sdl2_ttf/2.0.12/lib
SRCS	= $(wildcard $(SDIR)/*.cpp)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -lSDL2 -lSDL2_ttf
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR);

$(addprefix $(ODIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS) -D_THREAD_SAFE
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
