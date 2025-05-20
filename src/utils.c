#include "minishell.h"

unsigned int	next_div_8(unsigned int n)
{
	while (n % 8)
		n++;
	return (n);
}
