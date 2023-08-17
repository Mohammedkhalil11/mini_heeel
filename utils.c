/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:58:59 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/10 16:07:32 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] || s1[i])
	{
		if (s2[i] != s1[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	printf("(%s)", str);
}

void	acc_join(t_join *z)
{
	z->i++;
	z->j++;
}

char	*ft_strjoin(char *s1, char *s2)
{
	t_join	*z;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s2 && s1)
		return (ft_strdup(s1));
	z = my_malloc(sizeof(t_join));
	len_join(z, s1, s2);
	if (!z->x)
		return (0);
	while (s1[z->i])
	{
		z->x[z->i] = s1[z->i];
		z->i++;
	}
	while (s2[z->j])
	{
		z->x[z->i] = s2[z->j];
		acc_join(z);
	}
	return (z->x[z->i] = '\0', z->x);
}
