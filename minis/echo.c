/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:11:44 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 17:00:35 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_n(char **input, int *isoption, int *flprnt)
{
	int	j;

	j = 0;
	if (!input || !input[0])
	{
		printf ("\n");
		g_g.exit_status = 0;
		return (-7);
	}
	if (input[0][0] == '-' && input[0][j + 1] == 'n')
	{
		while (input[0][j + 1] == 'n')
		{
			if (input[0][j + 1] != 'n')
			{
				*isoption = 0;
				break ;
			}
			j++;
		}
	}
	if (input[0][0] == '-' && input[0][j + 1] == '\0' && !(*flprnt))
		*isoption = 1;
	return (j);
}

void	print_input(char **input, int *i, int *j, int *flprnt)
{
	if (input[*i][*j] && (input[*i][*j] != '\0' || *flprnt))
	{
		*flprnt = 1;
		printf("%s", &input[*i][*j]);
	}
	if ((input[*i][*j] != '\0' || *flprnt) && input[*i + 1] != NULL)
		printf(" ");
}

void	t_echo(char **input)
{
	int		isoption;
	int		i;
	int		flprnt;
	int		j;

	flprnt = 0;
	i = 0;
	isoption = 0;
	if (check_for_n(input, &isoption, &flprnt) == -7)
		return ;
	if (isoption)
		i = 1;
	j = 0;
	while (input[i])
	{
		print_input(input, &i, &j, &flprnt);
		i++;
	}
	if (!isoption)
		printf("\n");
	g_g.exit_status = 0;
}
