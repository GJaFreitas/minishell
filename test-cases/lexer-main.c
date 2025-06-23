#include "lexer.h"
#include "minishell.h"
#include "structs.h"

void	print_tokens_test(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}

// Display prompt and read the next line given to it
void	prompt()
{
	char	*line;
	char	**tok;

	line = get_next_line(0);
	tok = lexer(line);
	print_tokens_test(tok);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	prompt();
	return (0);
}
