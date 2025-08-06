# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g -Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = minishell

NODIR = --no-print-directory

# --- DEPENDENCIES ---------------- #

LIBFT = libft/libft.a

LIBFT_DIR = ./libft

# --- VPATH ------------ #
VPATH = src:src/functions:src/memory:src/signals:test-cases/

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
       env_to_array.c \
	   env_to_array_2.c \
	   env.c \
	   env_2.c \

# Exec sources
VPATH += src/exec
SRCS += \
       exec.c \
       heredoc.c \
	   Builtin.c \
	   redir_utils.c \

# Builtin functions sources
VPATH += src/functions
SRCS += \
	ft_export.c \
	ft_cd.c \
	ft_env.c \
	ft_echo.c \
	ft_exit.c \
	ft_pwd.c \
	ft_unset.c \
	export_utils\

# Lexer sources
VPATH += src/lexer
SRCS += lexer.c \
		lexer_tokenize.c \
		lex_utils.c \

# Memory sources
VPATH += src/memory
SRCS += \
	mem_alloc.c \
	mem_list.c \
	mem_test.c \

# Parser sources
VPATH += src/parser
SRCS += \
	parser.c \
	path_explore.c \
	cmd_assignement.c \
	parser_utils.c \
	expansions.c \

# Signal sources
VPATH += src/signals
SRCS += \
	signals.c \

# Utils sources
VPATH += src/utils
SRCS += \
	debug.c \
	utils.c \
# --- INCLUDES ---------------- #

INC =  -I./includes
INC += -I./libft

READLINE += -L/usr/local/lib -I/usr/local/include -lreadline

OBJS 		:= $(addprefix obj/,$(SRCS:.c=.o))
CORE_OBJS	:= $(filter-out obj/main.o,$(OBJS))

RM = rm -f

all: $(NAME)

obj:
	@mkdir -p obj

obj/%.o: %.c | obj
	@$(CC) -c $(INC) $(CFLAGS) $< -o $@


$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ $(READLINE)
	@echo "✓ built $(@F)"


$(LIBFT):
	@make -C libft $(NODIR)


# Tests

debug : $(OBJS) $(LIBFT) # Rule for the #ifdef
	@$(CC) $(CFLAGS) -D DEBUG $(INC) $^ -o $(NAME)
	@echo "✓ built $(NAME)"

bin:usr/local/lib -I/usr/local/include -lreadline
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

test_redirections:
	@$(MAKE) CFLAGS="-D TEST_REDIRECTIONS"
	@echo "✓ built with redirection tests"

.PHONY: all clean fclean re r test-% test_redirections
