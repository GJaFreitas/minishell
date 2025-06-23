#ifndef LEXER_H
# define LEXER_H

# define META_CHAR "|<>"
# define QUOTES "\'\""

int	special_char(char c);
char	**lexer(char *line);

#endif
