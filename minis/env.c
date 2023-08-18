/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:49:47 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 02:55:36 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

void	env(t_envar **ev, char **input)
{
	t_envar	*pr;

	pr = *ev;
	if (!input || !input[0])
	{
		while (pr)
		{
			if (ft_strchr(pr->value, '='))
			{
				write(1, pr->value, ft_strlen(pr->value));
				write(1, "\n", 1);
			}
			pr = pr->next;
		}
		g_g.exit_status = 0;
	}
	else
	{
		g_g.exit_status = 127;
		write(2, "env: ‘", 9);
		write(2, input[0], ft_strlen(input[0]));
		write(2, "’: No such file or directory\n", 32);
		return ;
	}
}
