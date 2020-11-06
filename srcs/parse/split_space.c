/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 21:57:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:23:50 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (TRUE);
	if (c == '\v' || c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}

static int	count_words(char const *s)
{
	int	result;
	int	is_word;

	result = 0;
	is_word = 0;
	while (*s)
	{
		if (is_word == 0 && !ft_isspace(*s))
			is_word = 1;
		if (is_word && ft_isspace(*s))
		{
			result++;
			is_word = 0;
		}
		s++;
	}
	if (is_word)
		result++;
	return (result);
}

int			free_strs(char **sep, int is_vaild_p, int word_locate)
{
	char	**next;
	int		locate;

	if (is_vaild_p)
	{
		next = sep;
		while (*next)
		{
			free(*next);
			next++;
		}
		free(sep);
		return (0);
	}
	locate = -1;
	while (++locate < word_locate - 1)
		free(sep[locate]);
	return (1);
}

static int	get_sep_word(char **sep, char const *s)
{
	int		word_size;
	int		word_locate;
	char	*start;

	word_size = 0;
	word_locate = 0;
	while (*s)
	{
		if (word_size == 0 && !ft_isspace(*s))
			start = (char *)s;
		if (word_size && ft_isspace(*s))
		{
			sep[word_locate] = ft_substr(start, 0, word_size);
			if (sep[word_locate++] == NULL)
				return (free_strs(sep, FALSE, word_locate));
			word_size = 0;
		}
		if (!ft_isspace(*s))
			word_size++;
		s++;
	}
	if (word_size)
		sep[word_locate++] = ft_substr(start, 0, word_size);
	sep[word_locate] = NULL;
	return (0);
}

char		**split_space(char const *s)
{
	int		words;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (result && get_sep_word(result, s))
	{
		free(result);
		result = NULL;
	}
	return (result);
}
