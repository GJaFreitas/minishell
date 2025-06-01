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
VPATH = src:src/functions:src/memory:src/signals
SRCS = \
       main.c \
       debug.c \
       exec.c \
       builtin.c \
       ft_echo.c \
       mem_alloc.c \
       mem_list.c \
       mem_test.c \
       utils.c \


# Lexer sources
VPATH += src/lexer
SRCS += \
	lexer.c \
	lexer_expansions.c \
	lexer_tokenize.c \
	lex_utils.c \


# Parser sources
VPATH += src/parser
SRCS += \
	parser.c \
	parser_quote_handler.c \
	cmd_assignement.c \
	parser_utils.c \
	parser_redirections.c \
	parser_options.c \
	parser_args.c \
	parser_token_merge.c \


# --- INCLUDES ---------------- #

INC = -L./includes -I./includes
INC += -L./libft -I./libft

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

RM = rm -f

all: $(NAME)

obj/%.o: %.c | obj
	@$(CC) -c $(INC) $(CFLAGS) $< -o $@

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
