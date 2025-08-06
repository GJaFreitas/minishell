/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sorted.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:52:31 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 20:09:19 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static t_env	*split(t_env *head)
{
	t_env	*fast;
	t_env	*slow;
	t_env	*temp;

	fast = head;
	slow = head;
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		if (fast != NULL)
		{
			slow = slow->next;
		}
	}
	temp = slow->next;
	slow->next = NULL;
	return (temp);
}

static t_env	*merge(t_env *first, t_env *second)
{
	if (first == NULL)
		return (second);
	if (second == NULL)
		return (first);
	if (ft_strcmp(first->key, second->key) < 0)
	{
		first->next = merge(first->next, second);
		return (first);
	}
	else
	{
		second->next = merge(first, second->next);
		return (second);
	}
}

static t_env	*merge_sort(t_env *head)
{
	t_env	*second;

	if (head == NULL || head->next == NULL)
		return (head);
	second = split(head);
	head = merge_sort(head);
	second = merge_sort(second);
	return (merge(head, second));
}

static t_env	*__copy_env(t_env *env)
{
	t_env	*cur;
	t_env	*start;

	cur = malloc(sizeof(t_env));
	start = cur;
	ft_memcpy(cur, env, sizeof(t_env));
	while (env)
	{
		cur->next = malloc(sizeof(t_env));
		ft_memcpy(cur->next, env->next, sizeof(t_env));
		env = env->next;
		cur = cur->next;
	}
	return (start);
}

t_env	*sort_env(t_env *env)
{
	t_env	*env_copy;

	env_copy = __copy_env(env);
	env_copy = merge_sort(env_copy);
	return (env_copy);
}

void	print_sorted_env(t_env *env)
{
	t_env	*sorted;
	t_env	*cur;

	sorted = sort_env(env);
	cur = sorted;
	while (cur)
	{
		cur = sorted;
		if (cur->exported)
			ft_printf("%s=%s\n", cur->key, cur->value);
		else
			ft_printf("%s\n", cur->key);
		cur = cur->next;
	}
	free_env_list(sorted);
}
