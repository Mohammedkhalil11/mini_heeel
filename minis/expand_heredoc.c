/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:47:21 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 06:52:36 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	acc_j_her(char *str, t_bill *b)
{
	while (str[b->i])
	{
		str[b->i] = str[b->i + 1];
		b->i++;
	}
}

char	*check_bill_her(char *str, t_env *senv, t_envar *env)
{
	t_bill	*bill;

	bill = my_malloc(sizeof(t_bill));
	bill->i = 0;
	while (str[bill->i])
	{
		if ((str[bill->i] == '"' || str[bill->i] == '\'')
			&& str[bill->i + 1] == '$')
			acc_j_her(str, bill);
		if (str[bill->i] == '$' && str[bill->i] != '"' && str[bill->i] != '\'')
			str = done_normal_her(str, senv, env, bill);
		if (bill->i < ft_strlen(str))
			bill->i++;
	}
	return (str);
}

char	*done_normal_her(char *str, t_env *senv, t_envar *env, t_bill *bill)
{
	char	*bef;
	char	*buffer;
	char	*rest;

	senv->var = fill_var_her(str, env, bill->i);
	senv->path = NULL;
	senv->path = fill_path_her(env, senv);
	bef = ft_substr(str, 0, bill->i);
	rest = ft_substr(str, bill->i + ft_strlen(senv->var) + 1, 10000);
	if (my_strcmp(bef, NULL) == 0)
		buffer = ft_strjoin(NULL, senv->path);
	else
		buffer = ft_strjoin(bef, senv->path);
	str = ft_strjoin(buffer, rest);
	bill->i = ft_strlen(buffer) - 1;
	return (str);
}

char	*fill_var_her(char *str, t_envar *env, int i)
{
	char	*var;
	int		x;

	(void)env;
	if (!str)
		return (NULL);
	var = my_malloc(sizeof(char) * 100);
	x = 0;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\n')
	{
		var[x] = str[i];
		i++;
		x++;
	}
	var[x] = '\0';
	return (var);
}

char	*fill_path_her(t_envar *env, t_env *s)
{
	int		j;
	char	*path;

	j = 0;
	path = my_malloc(sizeof(char) * 100);
	while (env->value[j] && env->value[j] != '=')
		j++;
	j++;
	while (env->next)
	{
		if (!ft_strncmp(s->var, var_gett(env)))
		{
			path = get_path(env);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}
