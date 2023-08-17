/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:28:40 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 06:44:29 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_g;

int	my_strcmp(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (1);
	if (!s2 && s1)
		return (1);
	return (0);
}

void	re_vars(t_main *main)
{
	main->i = 0;
	main->j = 0;
	main->x = 0;
}

void	done_normal(t_commandes *tmp, t_env *senv, t_envar *env, t_bill *bill)
{
	char	*bef;
	char	*buffer;
	char	*rest;

	senv->var = fill_var(tmp, env, bill->i, bill->j);
	senv->path = NULL;
	senv->path = fill_path(env, senv);
	if (senv->var[0] == '?' && senv->var[1] == '\0')
		senv->path = ft_itoa(g_g.exit_status);
	bef = ft_substr(tmp->commande[bill->i], 0, bill->j);
	rest = ft_substr(tmp->commande[bill->i],
			bill->j + ft_strlen(senv->var) + 1, 10000);
	if (my_strcmp(bef, NULL) == 0)
		buffer = ft_strjoin(NULL, senv->path);
	else
		buffer = ft_strjoin(bef, senv->path);
	free(tmp->commande[bill->i]);
	tmp->commande[bill->i] = ft_strjoin(buffer, rest);
	bill->j = ft_strlen(buffer) - 1;
	return ;
}

void	check_bill(t_commandes *tmp, t_env *senv, t_envar *env)
{
	t_bill	*b;

	b = my_malloc(sizeof(t_bill));
	while (tmp->commande[b->i])
	{
		b->j = 0;
		while (tmp->commande[b->i][b->j])
		{
			while (tmp->commande[b->i][b->j] == '"' || tmp->commande[b->i][b->j] == '\'')
				b->j++;
			if (tmp->commande[b->i][b->j] == '$'
				&& tmp->commande[b->i][b->j + 1] != '"'
				&& tmp->commande[b->i][b->j + 1] != '\'')
				done_normal(tmp, senv, env, b);
			if (b->j < ft_strlen(tmp->commande[b->i]))
				b->j++;
		}
		b->i++;
	}
}

void	siginthandler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
