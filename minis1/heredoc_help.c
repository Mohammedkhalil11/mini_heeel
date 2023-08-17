/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:55:52 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:58:47 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_signal(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

void	get_last_inf(char *list, int *flag, int *i, int *counter)
{
	if (list[*i] == '8' && list[*i + 1] && list[*i + 1] == '8')
	{
		*flag = 1;
		*i += 2;
	}
	else if (list[*i] == '4')
	{
		*flag = 0;
		*i += 1;
	}
	else if (list[*i] == '6' && *flag)
	{
		*counter += 1;
		*i += 1;
		*flag = 0;
	}
	else
		*i += 1;
}

int	count_last_inf_heredoc(char *list)
{
	int	i;
	int	flag;
	int	counter;

	counter = 0;
	flag = 0;
	i = 0;
	if (!list)
		return (0);
	while (list[i])
		get_last_inf(list, &flag, &i, &counter);
	if (flag)
		counter++;
	return (counter);
}

int	handle_heredoc(t_herdc *a, t_varint *l)
{
	if (a->pid[a->j] < 0)
	{
		printf("Minishel: error fork\n");
		return (-1);
	}
	if (a->pid[a->j] == 0)
		child_heredoc(a, l);
	else
	{
		if (parent_heredoc(a, l) == -1)
			return (-1);
	}
	l->x++;
	a->j++;
	a->o += 2;
	return (0);
}

int	check_last_heredoc(char	*list)
{
	int	i;
	int	fg;

	if (!list)
		return (0);
	i = 0;
	fg = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			fg = 1;
			i += 2;
		}
		else if (list[i] == '4')
		{
			fg = 0;
			i++;
		}
		else
			i++;
	}
	return (fg);
}
