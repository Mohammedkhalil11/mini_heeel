/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:37 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 01:20:12 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_line(t_main *main)
{
	g_g.readline = 1;
	main->line = readline("Minishell$ ");
	g_g.readline = 0;
	tcsetattr(0, TCSANOW, &main->term2);
	add_history(main->line);
	if (main->line == NULL)
		exit(0);
	if (main->line)
	{
		main->m = my_malloc(sizeof(t_commandes));
		main->tmp = main->m;
		main->list = toknz_list(main->line, 0, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_main	*main;
	t_envar	*ev;

	(void)ac;
	(void)av;
	ev = 0;
	ev = get_env(ev, env);
	main = my_malloc(sizeof(t_main));
	int_main(main);
	signal_handler();
	// int in = dup(0);
	// printf("iiiin %d\n", in);
    while (1)
    {
        int_sig_main(main);
        ft_read_line(main);
        if (!error_parss(main->list))
        {
        if (main->list && main->line
            && (*return_commande(main->list, main->line, 1, 0)
                || *return_file(main->list, main->line, 1, main->tmp)))
            int_main_before(main, ev);
        do_after_pipe(main, ev);
        multiple_pipe(&main->m, &ev, main->list, &main->senv);
		//dup2(0, in);
		// close(in);
		// printf("close\n");
        if (main->line)
            free(main->line);
        }
        re_vars(main);
    }
}