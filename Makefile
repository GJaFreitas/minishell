# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g #-Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = minishell

NODIR = --no-print-directory

# --- DEPENDENCIES ---------------- #

LIBFT = libft/libft.a

LIBFT_DIR = ./libft

# --- VPATH ------------ #
VPATH = src:src/functions:src/signals:test-cases/

# --- TESTS ------------ #

TEST_DRIVERS = \
	       lexer-main.c \

TEST_NAMES   := $(TEST_DRIVERS:-main.c=)
TEST_BINS    := $(addprefix bin/test-,$(TEST_NAMES))

# --- SOURCES ------------ #

# Misc or Unorganized as of yet sources
SRCS = \
       main.c \

# Env sources
VPATH += src/env
SRCS += \
	env.c \
	env_add_remove.c \
	env_array.c \
	env_internal_utils.c \
	env_sort.c \
	env_utilities.c \

# Exec sources
VPATH += src/exec
SRCS += \
	exec.c \
	redir_utils.c \

# Builtin functions sources
VPATH += src/functions
VPATH += src/functions/cd
SRCS += \
	ft_export.c \
	ft_cd.c \
	path_search.c \
	path_exists.c \
	ft_env.c \
	ft_echo.c \
	ft_exit.c \
	ft_pwd.c \
	ft_unset.c \

# Lexer sources
VPATH += src/lexer
SRCS += lexer.c \
		lexer_tokenize.c \
		lex_utils.c \

# Parser sources
VPATH += src/parser:src/parser/heredoc
SRCS += \
	parser.c \
	path_explore.c \
	cmd_assignement.c \
	parser_utils.c \
	expansions.c \
	heredoc.c \

# Signal sources
VPATH += src/signals
SRCS += \
	signals.c \

# Utils sources
VPATH += src/utils
SRCS += \
	debug.c \
	ft_strndup.c \
	ft_strcmp.c \
	ft_itoa_buf.c \


# --- INCLUDES ---------------- #

INC =  -I./includes
INC += -I./libft
#INC += -L/usr/local/lib -lreadline
INC +=-I/usr/local/include 

OBJS 		:= $(addprefix obj/,$(SRCS:.c=.o))
CORE_OBJS	:= $(filter-out obj/main.o,$(OBJS))

RM = rm -f

all: $(NAME)

obj:
	@mkdir -p obj

obj/%.o: %.c | obj
	@$(CC) -c $(INC) $(CFLAGS) $< -o $@


$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) -lreadline $^ -o $@
	@echo "✓ built $(@F)"


$(LIBFT):
	@make -C libft $(NODIR)


# Tests

debug : $(OBJS) $(LIBFT) # Rule for the #ifdef
	@$(CC) $(CFLAGS) -D DEBUG $(INC) $^ -o $(NAME)
	@echo "✓ built $(NAME)"

bin:
	@mkdir -p bin

bin/test-%: $(CORE_OBJS) obj/%-main.o $(LIBFT) | bin
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ 
	@echo "✓ built $(@F)"


test-%: bin/test-%		# Rule for automatically running tests
	@echo "✓ $< is built"
	@echo "Running tests..."
	clear
	./test.sh $*


clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) clean $(NODIR)
	@echo "✓ removing all objs"

fclean:
	@rm -rf obj
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean $(NODIR)
	@echo "✓ removing all"

re:
	@make fclean $(NODIR)
	@make $(NODIR)

r:
	make re && clear && ./$(NAME)

leaks:
	make re && clear && valgrind --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=readline.supp ./$(NAME)


.PHONY: all clean fclean re r test-% test_redirections
