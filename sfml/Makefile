CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++11 -stdlib=libc++
NAME	= ../sfml.so
SDIR	= srcs
ODIR	= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/.objs
INCS	= -I incs -I ../incs -I ~/.brew/include
LIBS	= -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics
SRCS	= $(wildcard $(SDIR)/*.cpp)
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -shared $(LIBS)
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

$(ODIR):
	/bin/mkdir -p $(ODIR)/$(SDIR);

$(addprefix $(ODIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS) -fPIC -g
	printf '%s\n' "Building object for $<"

clean:
	/bin/rm -rf $(ODIR)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) library is cleaned."

fclean:
	/bin/rm -rf $(ODIR)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) library is fcleaned."

re: fclean all

.PHONY: all clean fclean re
.SILENT:
