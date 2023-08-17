/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_it_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:57:46 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:37:55 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_down(t_tokenz *m)
{
	m->i--;
	m->j--;
}

void	redi_is_more(char *str, t_tokenz *m)
{
	if (ft_isspace(str[m->i]))
		m->array[m->j] = '2';
	else
		m->array[m->j] = '*';
}

void	red_red(char *str, t_tokenz *m, char token)
{
	if (ft_isredi(str[m->i]) || ft_issospecial(str[m->i]))
	{
		m->array[m->j] = token;
		plus_plus(m);
	}
}

void	red_q(char *str, t_tokenz *m)
{
	if (str[m->i] == '"' || str[m->i] == '\'')
	{
		m->array[m->j] = '3';
		plus_plus(m);
	}
}
