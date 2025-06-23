# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 15:16:20 by gjacome-          #+#    #+#              #
#    Updated: 2025/06/23 18:58:06 by gvon-ah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = libft.a

# --- DEPENDENCIES ---------------- #

###▼▼▼<src-updater-do-not-edit-or-remove>▼▼▼

SRCS = \
	srcs/misc/ft_isalpha.c \
	srcs/misc/ft_isspace.c \
	srcs/misc/ft_isascii.c \
	srcs/misc/ft_isalnum.c \
	srcs/misc/ft_isdigit.c \
	srcs/misc/ft_isprint.c \
	srcs/files/ft_putchar_fd.c \
	srcs/files/ft_putstr_fd.c \
	srcs/files/ft_putnbr_fd.c \
	srcs/files/ft_putendl_fd.c \
	srcs/memory/ft_memset.c \
	srcs/memory/ft_memcpy.c \
	srcs/memory/ft_memmove.c \
	srcs/memory/ft_memcmp.c \
	srcs/memory/ft_memchr.c \
	srcs/memory/ft_calloc.c \
	srcs/memory/ft_realloc.c \
	srcs/memory/ft_bzero.c \
	srcs/lists/ft_lstdelone.c \
	srcs/lists/ft_lstmap.c \
	srcs/lists/ft_lstnew.c \
	srcs/lists/ft_lstadd_front.c \
	srcs/lists/ft_lstadd_back.c \
	srcs/lists/ft_lstsize.c \
	srcs/lists/ft_lstiter.c \
	srcs/lists/ft_lstclear.c \
	srcs/lists/ft_lstlast.c \
	srcs/strings/ft_strjoin.c \
	srcs/strings/ft_itoa.c \
	srcs/strings/ft_strncmp.c \
	srcs/strings/ft_substr.c \
	srcs/strings/ft_strnstr.c \
	srcs/strings/ft_strlcpy.c \
	srcs/strings/ft_strrchr.c \
	srcs/strings/ft_striteri.c \
	srcs/strings/ft_strlcat.c \
	srcs/strings/ft_strlen.c \
	srcs/strings/ft_tolower.c \
	srcs/strings/ft_strchr.c \
	srcs/strings/ft_atoi.c \
	srcs/strings/ft_toupper.c \
	srcs/strings/ft_strtrim.c \
	srcs/strings/ft_strmapi.c \
	srcs/strings/ft_split.c \
	srcs/strings/ft_strdup.c \
	ft_printf/ft_charint.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_aux.c \
	ft_printf/ft_hex.c \
	ft_printf/ft_nexus.c \
	get_next_line/get_next_line_utils.c \
	get_next_line/get_next_line.c \

###▲▲▲<src-updater-do-not-edit-or-remove>▲▲▲

OBJS_DIR = objs

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

DEPS = libft.h

HEAD = includes

RM = rm -rf

AR = ar rcs

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)	$(NODIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(NODIR)

$(NAME) : $(OBJS)
	@echo "✓ libft compiled"
	@$(AR) $(NAME) $(OBJS)

clean:
	@echo "✓ cleaning in libft"
	@$(RM) $(OBJS_DIR)

fclean:
	@echo "✓ deepcleaning in libft"
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)

re:
	@make fclean $(NODIR)
	@make $(NODIR)

.PHONY: all clean fclean re
