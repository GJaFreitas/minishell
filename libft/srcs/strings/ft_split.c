/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:16:44 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/29 19:24:24 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	destroy(char ***arr)
{
	int	i;

	i = 0;
	while (**arr != NULL)
	{
		free(*arr[i]);
		i++;
	}
	*arr = NULL;
}

static void	allocpy(char **arr, char *s)
{
	char	*temp;
	char	**arr_cpy;

	temp = s;
	arr_cpy = arr;
	while (*temp)
	{
		while (ft_isspace(*s))
			s++;
		temp = s;
		while (*temp && !ft_isspace(*temp))
			temp++;
		if (ft_isspace(*temp) || temp > s)
		{
			*arr = ft_substr(s, 0, temp - s);
			if (*arr == NULL)
				return (destroy(&arr_cpy));
			s = temp;
			++arr;
		}
	}
	*arr = NULL;
}

static int	count_words(char const *s)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			++word_count;
		while (*s && !ft_isspace(*s))
			++s;
	}
	return (word_count);
}

char	**ft_split(char const *s)
{
	char	**arr;
	int		words;

	if (!*s)
	{
		arr = malloc(sizeof(char *));
		if (!arr)
			return (NULL);
		*arr = NULL;
		return (arr);
	}
	words = count_words(s);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	allocpy(arr, (char *)s);
	return (arr);
}
