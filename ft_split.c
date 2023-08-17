/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:27 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/03 10:21:59 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
	return (count);
}

static void	free_all(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		free(str[j]);
		j++;
	}
	free(str);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*c;
	int		i;
	int		y;

	i = 0;
	y = ft_strlen(s);
	if (len == 0)
		return (0);
	if (len > y - start)
		len = y - start;
	c = my_malloc(sizeof(char) * (len + 1));
	if (!c)
		return (0);
	if (start > y)
	{
		c[i] = '\0';
		return (c);
	}
	while (s[start] && i < len)
	{
		c[i] = s[start];
		start++;
		i++;
	}
	return (c[i] = '\0', c);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = -1;
	if (!s)
		return (NULL);
	p = my_malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!p)
		return (NULL);
	while (++l < count_words((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		p[l] = ft_substr(s, j, i - j);
		if (!p[l])
			return (free_all(p), NULL);
	}
	return (p[l] = NULL, p);
}
