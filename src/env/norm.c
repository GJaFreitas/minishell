#include "minishell.h"

t_cmd	*norm(t_cmd *cmd)
{
	static t_cmd	*this;

	if (!this)
		this = cmd;
	if (cmd == NULL)
		return (this);
	return (NULL);
}
