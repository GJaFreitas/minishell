#ifndef LEXER_H
# define LEXER_H

# define META_CHAR "\"\'|<>"

int	special_char(char c);
char	**lexer(char *line);

#endif
