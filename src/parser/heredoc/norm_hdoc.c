#include "minishell.h"
#include "parser.h"

t_hdoc  *hdoc_norm(t_hdoc *ptr)
{
    static t_hdoc  *this;

    if (ptr)
        this = ptr;
    else
        return (this);
    return (NULL);
}