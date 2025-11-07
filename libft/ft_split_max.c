/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:54:31 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/07 13:03:55 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_str(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	get_words(char *str, char *charset)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (in_str(charset, str[i]))
			i++;
		if (!in_str(charset, str[i]))
		{
			c++;
			while (!in_str(charset, str[i]) && str[i])
				i++;
		}
	}
	return (c);
}

int	len_word_charset(char *str, char *charset, int pos)
{
	int	i;

	i = 0;
	if (in_str(charset, str[pos]))
	{
		while (in_str(charset, str[pos++]))
			i++;
	}
	else
	{
		while (!in_str(charset, str[pos]) && str[pos++])
			i++;
	}
	return (i);
}

char	**ft_split_max(char *str, char *charset)
{
	char	**res;
	int		i;
	int		j;

	res = malloc(sizeof(char *) * (get_words(str, charset) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (in_str(charset, str[i]))
			i += len_word_charset(str, charset, i);
		else
		{
			res[j] = ft_strndup(&str[i], len_word_charset(str, charset, i));
			i += len_word_charset(str, charset, i);
			j++;
		}
	}
	res[j] = 0;
	return (res);
}
