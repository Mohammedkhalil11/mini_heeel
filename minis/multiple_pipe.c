/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:00:00 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 06:28:25 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_pipe_init(t_exeec *z, t_commandes **c, char *list)
{
	z->pipe_fd[0] = -1;
	z->pipe_fd[1] = -1;
	z->t = count_last_inf_heredoc(list);
	z->cmd = *c;
	z->l->size = count_heredoc(list);
	z->l->pipe_fd[0] = -1;
	z->l->pipe_fd[1] = -1;
	z->s = ft_lst_size(*c);
	z->i = 0;
	z->l->fd_rdc = my_malloc(sizeof(int) * z->t);
	z->l->nb_h = 0;
	z->l->k = 0;
	z->cp = NULL;
}

void	multiple_pipe(t_commandes **c, t_envar **ev, char *list, t_env **eev)
{
	t_exeec	*z;

	z = my_malloc(sizeof(t_exeec));
	if (list[0])
	{
		z->l = my_malloc(sizeof(t_varint));
		z->l->s = *eev;
		z->l->env = *ev;
		multiple_pipe_init(z, c, list);
		if (z->s == 1)
		{
			single_node_exec(z, list, ev);
			return ;
		}
		else if (z->s > 1)
		{
			if (bigger_than_one(list, c, z, ev))
				return ;
		}
	}
	return ;
}
