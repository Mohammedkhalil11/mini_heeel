/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:20:53 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/11 01:31:02 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    quotes_error(char *list)
{
    int    num;
    int    num1;

    num = num_of_q(list, 0);
    num1 = num_of_s_q(list, 0);
    if (num % 2 != 0 || num1 % 2 != 0)
        return(lerreurat(3));
    return (0);
}

int    expand_erreur(char *list)
{
    int    i;

    i = 0;
    if (!list)
        return (0);
    while (list[i])
    {
        if(ft_isredi(list[i]))
        {
            i = i + 2;
            if (ft_isredi(list[i]) || !list[i] || ft_issospecial(list[i]))
                {printf("i ->%d and list[i] ->%c\n", i, list[i]);
                return(lerreurat(9));}
        }    
        i++;
    }
    return (0);
}

int    error_parss(char *list)
{
    if (check_pipe(list) || quotes_error(list))
        return (1);
    return (0);
}

int    check_pipe(char *list)
{
    int    i;
    if (list[0] == '6')
        return(lerreurat(6));
    i = ft_strlen(list) - 1;
    if (i >= 0)
    {
        if (list[i] == '6')
            return(lerreurat(6));
        while (list[i] == '2')
             i--;
        if (list[i] == '6')
            return (lerreurat(6));
    }
    return (0);
}

int    lerreurat(int error)
{
    if (error == 3)
    {
        write(2, "ERROR: parse error near quote\n", 30);
        return (3);
    }
    if (error == 6)
    {
        write(2, "ERROR: parse error near `|'\n", 28);
        return (6);
    }
    if (error == 9)
    {
        write(2, "ERROR REDIRECTION!\n", 20);
        return (9);
    }
    return (0);
}
