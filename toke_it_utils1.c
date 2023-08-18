/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_it_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:11:32 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:29:25 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xsqbp(t_tokenz *m, char *str)
{
	m->i++;
	m->j++;
	m->count++;
	while (m->i < find_quotes_pair(str, '\''))
		xsfill_it(m, str);
	if (str[m->i] == '\'')
		m->array[m->j] = '0';
}

void	dquotes_tokenz(t_tokenz *m, char *str)
{
	m->array[m->j] = '3';
	if (quote_bfr_pipe(str, m->i, '"'))
		dqbp(m, str);
	else if (!quote_bfr_pipe(str, m->i, '"'))
		xdqbp(m, str);
}

void	squotes_tokenz(t_tokenz *m, char *str)
{
	m->array[m->j] = '0';
	if (quote_bfr_pipe(str, m->i, '\''))
		sqbp(m, str);
	else if (!quote_bfr_pipe(str, m->i, '\''))
		xsqbp(m, str);
}

void	redi_tokenz(t_tokenz *m, char *str, char token)
{
	int	lock;

	lock = 0;
	m->array[m->j] = token;
	plus_plus(m);
	if (ft_isredi(str[m->i]) || ft_issospecial(str[m->i]))
	{
		m->array[m->j] = token;
		return ;
	}
	while (m->i <= ft_strlen(str) && (ft_isspace(str[m->i])
			|| ft_isprintbl(str[m->i])) && !ft_issospecial(str[m->i])
		&& str[m->i] && !lock)
	{
		redi_is_more(str, m);
		if (is_pss(str[m->i]))
		{
			if (skip_it(str, m, token))
				return ;
			lock = 1;
		}
		plus_plus(m);
	}
	ft_down(m);
}

void	double_redi_tokenz(t_tokenz *m, char *str, char token)
{
	int	lock;

	lock = 0;
	m->array[m->j] = token;
	plus_plus(m);
	m->array[m->j] = token;
	plus_plus(m);
	red_red(str, m, token);
	red_q(str, m);
	while (m->i <= ft_strlen(str) && str[m->i] && (ft_isspace(str[m->i])
			|| ft_isprintbl(str[m->i])) && !ft_issospecial(str[m->i]) && !lock)
	{
		starting(str, m);
		if (ft_isprintbl(str[m->i]) && !ft_issospecial(str[m->i])
			&& !ft_isspace(str[m->i]))
		{
			fill_in_double(str, m, token);
			lock = 1;
		}
		plus_plus(m);
	}
	ft_down(m);
}
