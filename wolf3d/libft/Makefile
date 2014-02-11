# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 11:37:56 by prenvois          #+#    #+#              #
#    Updated: 2014/02/11 15:29:52 by prenvois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
CHECK = -Weverything -g3 -fno-inline -DD_ERRORS_ON -O2
NAME = libft.a
HDIR = includes
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c ft_realloc.c \
	   ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	   ft_strncat.c ft_strlcat.c ft_strchr.c ft_strnchr.c ft_strrchr.c \
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_strnew.c \
	   ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	   ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	   ft_strtrim.c ft_strsplit.c ft_strsplittoi.c ft_strwsplit.c ft_strrev.c \
	   ft_revcase.c get_next_line.c ft_printf.c \
	   ft_itoa.c ft_uitoa.c ft_uitoxa.c ft_luitoxa.c ft_uitooa.c ft_atof.c \
	   ft_atoi.c ft_sqrt.c ft_abs.c ft_dabs.c ft_cos.c ft_sin.c \
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_toupper.c ft_tolower.c \
	   ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_lstnew.c ft_lstadd.c ft_lstaddend.c ft_lstaddat.c ft_lstnew_or_add.c \
	   ft_lstdelone.c ft_lstdel.c ft_lstclr.c ft_lstiter.c ft_lstmap.c \
	   ft_lstsplit.c ft_lstsize.c ft_lstget.c ft_lstprint.c ft_lstquicksort.c \
	   ft_lstswap.c ft_lstbblsort.c \
	   ft_llstnew.c ft_llstadd.c ft_llstaddend.c ft_llstaddat.c ft_llstdel.c \
	   ft_llstnew_or_add.c ft_llstprint.c \
	   ft_cllstnew.c ft_cllstadd.c ft_cllstaddend.c ft_cllstaddat.c \
	   ft_cllstnew_or_add.c ft_cllstdel.c ft_cllstclr.c ft_cllstprint.c \
	   ft_bnew.c ft_badd.c ft_bnew_or_add.c ft_bsearch.c ft_bprint.c ft_bclr.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$@ created!"

%.o : %.c $(HDIR)
	$(CC) $(CFLAGS) -c $< -I $(HDIR)
	printf '%s\n' "Building object for $<"

test:
	$(CC) $(CFLAGS) main.c -L. -lft -I $(HDIR)

check: CFLAGS = $(CHECK)
check: re

clean:
	/bin/rm -rf $(OBJS)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is cleaned."

fclean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(NAME)
	printf '\033[32;03m%s\033[00m\n' "$(NAME) directory is fcleaned."

re: fclean all

.PHONY: all, test, check, clean, fclean, re
.SILENT:
