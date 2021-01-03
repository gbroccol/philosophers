/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/03 20:47:20 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				main(int argc, char **argv)
{
	t_com 		com;
	t_phil		*phil;
	t_table		*table;
	t_all		*all;
	pthread_t			thread;
	unsigned int		i;

	memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		error();
	else
	{
		phil = init_phil(com.phil_nmb);
		table = init_table(com.phil_nmb);
		all = init_all(&com, phil, table); // error
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_create(&(all[i].phil->thread), NULL, action, (void *)(&all[i]));
			usleep(50);
			i++;
		}
		pthread_create(&thread, NULL, phil_die, (void *)(all));
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_join(&(all[i].phil->thread[i]), NULL);
			i++;
		}
		pthread_join(thread, NULL);
	}
	return (0);
}
