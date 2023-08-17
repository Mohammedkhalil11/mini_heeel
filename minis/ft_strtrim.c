/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:29:53 by iszitoun          #+#    #+#             */
/*   Updated: 2022/10/27 20:29:54 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	first;
	int	last;

	if (!s1 || !set)
		return (0);
	first = 0;
	last = ft_strlen(s1) - 1;
	while (s1[first] && ft_set(s1[first], set))
		first++;
	while (last > 0 && ft_set(s1[last], set))
		last--;
	if (last == -1)
		return (ft_substr(s1, first, 0));
	return (ft_substr(s1, first, (last - first + 1)));
}
