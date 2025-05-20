#ifndef STRUCTS_H
# define STRUCTS_H

// If cmd only has an outfile
# define OUTFILE 1

// If cmd only has an infile
# define INFILE 2

// If cmd has both and in and out file
# define IOFILES 3

typedef unsigned int t_uint;

typedef struct s_simplecmd
{
	char	*cmd;
	char	*opts;
	char	*args;

	int	ior;
	char	*outfile;
	char	*infile;

	int	pipe;
}	t_simplecmd;

typedef struct s_cmdtable
{
	t_simplecmd	**cmds;
	int	num_cmds;
}	t_cmdtbl;

// typedef enum	s_mchar
// {
// 	REDIRECT = 0,
// }	t_mchar;

#endif
