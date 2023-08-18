/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:51:55 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:07:47 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_hered_var(t_herdc *a, t_commandes **c, t_varint *l, char *list)
{
	a->m = -1;
	a->k = NULL;
	a->pid = my_malloc (sizeof(int) * l->size);
	l->tmp = (*c);
	a->i = 0;
	l->x = 0;
	a->j = 0;
	a->o = 0;
	a->in_file = get_first_infile(l->tmp->files, list);
}

int	parent_heredoc(t_herdc *a, t_varint *l)
{
	close(l->pipe_fd[1]);
	waitpid(a->pid[a->j], &(a->heredoc_status), 0);
	if (l->tmp->files[l->x] && !ft_strcmp(a->in_file, l->tmp->files[l->x]))
		l->nb_h++;
	if (WEXITSTATUS(a->heredoc_status) == 130)
	{
		g_g.exit_status = 130;
		return (-1);
	}
	else if (WIFEXITED(a->heredoc_status))
	{
		g_g.exit_status = 0;
		return (0);
	}
	return (0);
}

void	fill_sring(t_varint *l, t_herdc *a)
{
	if (l->line[0] != '\0' && l->tmp->files[l->x]
		&& !ft_str_ncmp(l->line, l->tmp->files[l->x],
			ft_strlen(l->line)))
	{
		if (!ft_strcmp(a->in_file, l->tmp->files[l->x]))
		{
			if (!a->m)
			{
				write(l->pipe_fd[1], a->k, ft_strlen(a->k));
				close(l->pipe_fd[1]);
			}
		}
		free(l->line);
		exit(0);
	}
	if (a->i == 0)
	{
		a->k = ft_strjoin(l->line, "\n");
		free(l->line);
	}
	else if (a->k)
		fill_str_l(a, l);
}

void	child_heredoc(t_herdc *a, t_varint *l)
{
	signal(SIGINT, here_doc_signal);
	signal(SIGQUIT, SIG_IGN);
	a->i = 0;
	while (1)
	{
		l->line = readline(">");
		a->tmp = l->line;
		if (!strchr(l->tmp->files[l->x], '$'))
			a->tmp = check_bill_her(a->tmp, l->s, l->env);
		l->line = a->tmp;
		fill_sring(l, a);
		a->i++;
	}
	exit(0);
}

int	heredoc(t_commandes **c, t_varint *l, char *list)
{
	t_herdc	a;

	init_hered_var(&a, c, l, list);
	while (list[a.o])
	{
		if (list[a.o] == '8' && list[a.o + 1] && list[a.o + 1] == '8')
		{
			if (l->tmp->files[l->x]
				&& !ft_strcmp(a.in_file, l->tmp->files[l->x]))
			{
				a.m = pipe(l->pipe_fd);
				if (a.m < 0)
					exit(EXIT_FAILURE);
				l->fd_rdc[l->nb_h] = l->pipe_fd[0];
			}
			a.pid[a.j] = fork();
			if (handle_heredoc(&a, l) == (-1))
				return (-1);
		}
		else
			a.o++;
	}
	return (0);
}
