# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 15:16:20 by gjacome-          #+#    #+#              #
#    Updated: 2025/04/29 19:20:16 by gjacome-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g -Wall -Wextra -Werror -O2

# --- NAME ---------------------- #

NAME = libft.a

# --- DEPENDENCIES ---------------- #

###▼▼▼<src-updater-do-not-edit-or-remove>▼▼▼
# **************************************************************************** #
# **   Generated with https://github.com/lorenuars19/makefile-src-updater   ** #
# **************************************************************************** #

SRCS = \
	./srcs/misc/ft_isalpha.c \
	./srcs/misc/ft_isspace.c \
	./srcs/misc/ft_isascii.c \
	./srcs/misc/ft_isalnum.c \
	./srcs/misc/ft_isdigit.c \
	./srcs/misc/ft_isprint.c \
	./srcs/files/ft_putchar_fd.c \
	./srcs/files/ft_putstr_fd.c \
	./srcs/files/ft_putnbr_fd.c \
	./srcs/files/ft_putendl_fd.c \
	./srcs/memory/ft_memset.c \
	./srcs/memory/ft_memcpy.c \
	./srcs/memory/ft_memmove.c \
	./srcs/memory/ft_memcmp.c \
	./srcs/memory/ft_memchr.c \
	./srcs/memory/ft_calloc.c \
	./srcs/memory/ft_realloc.c \
	./srcs/memory/ft_bzero.c \
	./srcs/lists/ft_lstdelone.c \
	./srcs/lists/ft_lstmap.c \
	./srcs/lists/ft_lstnew.c \
	./srcs/lists/ft_lstadd_front.c \
	./srcs/lists/ft_lstadd_back.c \
	./srcs/lists/ft_lstsize.c \
	./srcs/lists/ft_lstiter.c \
	./srcs/lists/ft_lstclear.c \
	./srcs/lists/ft_lstlast.c \
	./srcs/strings/ft_strjoin.c \
	./srcs/strings/ft_itoa.c \
	./srcs/strings/ft_strncmp.c \
	./srcs/strings/ft_substr.c \
	./srcs/strings/ft_strnstr.c \
	./srcs/strings/ft_strlcpy.c \
	./srcs/strings/ft_strrchr.c \
	./srcs/strings/ft_striteri.c \
	./srcs/strings/ft_strlcat.c \
	./srcs/strings/ft_strlen.c \
	./srcs/strings/ft_tolower.c \
	./srcs/strings/ft_strchr.c \
	./srcs/strings/ft_atoi.c \
	./srcs/strings/ft_toupper.c \
	./srcs/strings/ft_strtrim.c \
	./srcs/strings/ft_strmapi.c \
	./srcs/strings/ft_split.c \
	./srcs/strings/ft_strdup.c \
	./ft_printf/ft_charint.c \
	./ft_printf/ft_printf.c \
	./ft_printf/ft_aux.c \
	./ft_printf/ft_hex.c \
	./ft_printf/ft_nexus.c \
	./get_next_line/get_next_line_utils.c \
	./get_next_line/get_next_line.c \

###▲▲▲<src-updater-do-not-edit-or-remove>▲▲▲

OBJS = $(SRCS:.c=.o)

DEPS = libft.h

HEAD = includes

RM = rm -f

AR = ar rc

RANLIB = ranlib

.c.o:
	@$(CC) -c $(CFLAGS) $< -o $(<:.c=.o) -I $(HEAD)

$(NAME) : $(OBJS)
	@echo "making in libft :)"
	@$(AR) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)

all: $(NAME)

clean:
	@echo "cleaning in libft"
	@$(RM) $(OBJS)

fclean:
	@echo "deepcleaning in libft"
	@make clean
	@$(RM) $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re
