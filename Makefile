# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 11:37:56 by prenvois          #+#    #+#              #
#    Updated: 2014/03/18 16:53:48 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
CHECK = -Weverything -g3 -fno-inline -DD_ERRORS_ON -O2
NAME = libft.a
HDIR = includes
SRCSDIR = srcs
SRCS = $(SRCSDIR)/ft_memset.c          \
	   $(SRCSDIR)/ft_bzero.c           \
	   $(SRCSDIR)/ft_memcpy.c          \
	   $(SRCSDIR)/ft_memccpy.c         \
	   $(SRCSDIR)/ft_memmove.c         \
	   $(SRCSDIR)/ft_memchr.c          \
	   $(SRCSDIR)/ft_memcmp.c          \
	   $(SRCSDIR)/ft_memalloc.c        \
	   $(SRCSDIR)/ft_memdel.c          \
	   $(SRCSDIR)/ft_realloc.c         \
	   $(SRCSDIR)/ft_strlen.c          \
	   $(SRCSDIR)/ft_strdup.c          \
	   $(SRCSDIR)/ft_strcpy.c          \
	   $(SRCSDIR)/ft_strncpy.c         \
	   $(SRCSDIR)/ft_strcat.c          \
	   $(SRCSDIR)/ft_strncat.c         \
	   $(SRCSDIR)/ft_strlcat.c         \
	   $(SRCSDIR)/ft_strchr.c          \
	   $(SRCSDIR)/ft_strnchr.c         \
	   $(SRCSDIR)/ft_strrchr.c         \
	   $(SRCSDIR)/ft_strstr.c          \
	   $(SRCSDIR)/ft_strnstr.c         \
	   $(SRCSDIR)/ft_strcmp.c          \
	   $(SRCSDIR)/ft_strncmp.c         \
	   $(SRCSDIR)/ft_strnew.c          \
	   $(SRCSDIR)/ft_strdel.c          \
	   $(SRCSDIR)/ft_strclr.c          \
	   $(SRCSDIR)/ft_striter.c         \
	   $(SRCSDIR)/ft_striteri.c        \
	   $(SRCSDIR)/ft_strmap.c          \
	   $(SRCSDIR)/ft_strmapi.c         \
	   $(SRCSDIR)/ft_strequ.c          \
	   $(SRCSDIR)/ft_strnequ.c         \
	   $(SRCSDIR)/ft_strsub.c          \
	   $(SRCSDIR)/ft_strjoin.c         \
	   $(SRCSDIR)/ft_strtrim.c         \
	   $(SRCSDIR)/ft_strsplit.c        \
	   $(SRCSDIR)/ft_strsplittoi.c     \
	   $(SRCSDIR)/ft_strwsplit.c       \
	   $(SRCSDIR)/ft_strrev.c          \
	   $(SRCSDIR)/ft_strrevcase.c      \
	   $(SRCSDIR)/get_next_line.c      \
	   $(SRCSDIR)/ft_printf.c          \
	   $(SRCSDIR)/ft_printf_fd.c       \
	   $(SRCSDIR)/ft_itoa.c            \
	   $(SRCSDIR)/ft_uitoa.c           \
	   $(SRCSDIR)/ft_uitoxa.c          \
	   $(SRCSDIR)/ft_luitoxa.c         \
	   $(SRCSDIR)/ft_uitooa.c          \
	   $(SRCSDIR)/ft_atof.c            \
	   $(SRCSDIR)/ft_atoi.c            \
	   $(SRCSDIR)/ft_sqrt.c            \
	   $(SRCSDIR)/ft_abs.c             \
	   $(SRCSDIR)/ft_dabs.c            \
	   $(SRCSDIR)/ft_cos.c             \
	   $(SRCSDIR)/ft_sin.c             \
	   $(SRCSDIR)/ft_isalpha.c         \
	   $(SRCSDIR)/ft_isdigit.c         \
	   $(SRCSDIR)/ft_isalnum.c         \
	   $(SRCSDIR)/ft_isascii.c         \
	   $(SRCSDIR)/ft_isprint.c         \
	   $(SRCSDIR)/ft_toupper.c         \
	   $(SRCSDIR)/ft_tolower.c         \
	   $(SRCSDIR)/ft_putchar.c         \
	   $(SRCSDIR)/ft_putstr.c          \
	   $(SRCSDIR)/ft_putendl.c         \
	   $(SRCSDIR)/ft_putnbr.c          \
	   $(SRCSDIR)/ft_putchar_fd.c      \
	   $(SRCSDIR)/ft_putstr_fd.c       \
	   $(SRCSDIR)/ft_putendl_fd.c      \
	   $(SRCSDIR)/ft_putnbr_fd.c       \
	   $(SRCSDIR)/ft_lstnew.c          \
	   $(SRCSDIR)/ft_lstadd.c          \
	   $(SRCSDIR)/ft_lstaddend.c       \
	   $(SRCSDIR)/ft_lstaddat.c        \
	   $(SRCSDIR)/ft_lstnew_or_add.c   \
	   $(SRCSDIR)/ft_lstiter.c         \
	   $(SRCSDIR)/ft_lstmap.c          \
	   $(SRCSDIR)/ft_strsplitlst.c     \
	   $(SRCSDIR)/ft_lstsize.c         \
	   $(SRCSDIR)/ft_lstget.c          \
	   $(SRCSDIR)/ft_lstprint.c        \
	   $(SRCSDIR)/ft_lstquicksort.c    \
	   $(SRCSDIR)/ft_lstswap.c         \
	   $(SRCSDIR)/ft_lstbblsort.c      \
	   $(SRCSDIR)/ft_lstmergesort.c   \
	   $(SRCSDIR)/ft_lstclr.c          \
	   $(SRCSDIR)/ft_lstdel.c          \
	   $(SRCSDIR)/ft_llstnew.c         \
	   $(SRCSDIR)/ft_llstnewnode.c     \
	   $(SRCSDIR)/ft_llstadd.c         \
	   $(SRCSDIR)/ft_llstaddend.c      \
	   $(SRCSDIR)/ft_llstaddat.c       \
	   $(SRCSDIR)/ft_llstdel.c         \
	   $(SRCSDIR)/ft_llstnew_or_add.c  \
	   $(SRCSDIR)/ft_llstprint.c       \
	   $(SRCSDIR)/ft_cllstnew.c        \
	   $(SRCSDIR)/ft_cllstadd.c        \
	   $(SRCSDIR)/ft_cllstaddend.c     \
	   $(SRCSDIR)/ft_cllstaddat.c      \
	   $(SRCSDIR)/ft_cllstnew_or_add.c \
	   $(SRCSDIR)/ft_cllstprint.c      \
	   $(SRCSDIR)/ft_cllstclr.c        \
	   $(SRCSDIR)/ft_cllstdel.c        \
	   $(SRCSDIR)/ft_bnew.c            \
	   $(SRCSDIR)/ft_badd.c            \
	   $(SRCSDIR)/ft_bnew_or_add.c     \
	   $(SRCSDIR)/ft_bsearch.c         \
	   $(SRCSDIR)/ft_bprint.c          \
	   $(SRCSDIR)/ft_bclr.c
OBJSDIR = .objs
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) created!"

$(OBJSDIR):
	/bin/mkdir $(OBJSDIR)
	/bin/mkdir $(OBJSDIR)/$(SRCSDIR)

$(addprefix $(OBJSDIR)/, %.o): %.c $(HDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HDIR)
	printf '%s\n' "Building object for $<"

check: CFLAGS = $(CHECK)
check: re

analyze: CFLAGS += --analyze
analyze: re

clean:
	/bin/rm -rf $(OBJSDIR)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is cleaned."

fclean:
	/bin/rm -rf $(OBJSDIR)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is fcleaned."

re: fclean all

.PHONY: all check analyze clean fclean re
.SILENT:
