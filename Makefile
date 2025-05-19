# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 15:16:20 by gjacome-          #+#    #+#              #
#    Updated: 2025/05/17 14:56:45 by gjacome-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g -Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = shell

NODIR = --no-print-directory

# --- DEPENDENCIES ---------------- #

LIBFT = libft/libft.a

# --- SOURCES ------------ #
VPATH = src:src/functions:src/memory
SRCS = \
       minishell.c \
       tokenize.c \
       exec.c \
       builtin.c \
       ft_echo.c \
       mem_alloc.c \
       mem_list.c \
       mem_test.c

# --- INCLUDES ---------------- #

INC = -L./includes -I./includes
INC += -L./libft -I./libft

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

RM = rm -f

all: $(NAME)

obj/%.o: %.c | obj
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

obj:
	mkdir -p obj

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME) 


$(LIBFT):
	@make -C libft $(NODIR)

clean:
	@rm -rf obj

fclean:	clean
	@$(RM) $(NAME)

re:
	@make fclean $(NODIR)
	@make $(NODIR)

r:
	make
	@./$(NAME)

.PHONY: all clean fclean re r
