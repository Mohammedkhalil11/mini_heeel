/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 05:15:50 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:33:54 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	acc_j(t_commandes *tmp, t_bill *b)
{
	while (tmp->commande[b->i][b->j])
	{
		tmp->commande[b->i][b->j] = tmp->commande[b->i]
		[b->j + 1];
		b->j++;
	}
}
