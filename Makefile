# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g -Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = msh

NODIR = --no-print-directory

# --- DEPENDENCIES ---------------- #

LIBFT = libft/libft.a

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


# --- INCLUDES ---------------- #

INC = -L./includes -I./includes
INC += -L./libft -I./libft

OBJS = $(addprefix obj/,$(SRCS:.c=.o))
CORE_OBJS  := $(filter-out obj/main.o,$(OBJS))

RM = rm -f

all: $(NAME)

obj:
	@mkdir -p obj

obj/%.o: %.c | obj
	@$(CC) -c $(INC) $(CFLAGS) $< -o $@


$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ 
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


test-%: bin/test-% # Rule for automatically running tests
	@echo "✓ $< is built"
	@echo "Running tests..."
	./test.sh $*


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

.PHONY: all clean fclean re r test-%
