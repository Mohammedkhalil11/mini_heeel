/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:11:40 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 18:43:15 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0' || !s1[i])
		return (0);
	else
		return (-s2[i - 1]);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_str_ncmp(char *s1, char *s2, int n)
{
	unsigned char	*k;
	unsigned char	*j;
	int				i;

	if (!s1 || !s2)
		return (-1);
	k = (unsigned char *)s1;
	j = (unsigned char *)s2;
	i = 0;
	while (n > 0 && i < n)
	{
		if (k[i] == '\0' || j[i] == '\0')
			return (k[i] - j[i]);
		if (k[i] == j[i])
		{
			if (i == (n))
				return (0);
		}
		if (k[i] > j[i])
			return (1);
		if (k[i] < j[i])
			return (-1);
		i++;
	}
	return (0);
}
