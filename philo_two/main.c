/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 21:21:27 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		error()
{
	write(1, "Error\nWrong arguments\n", 22);
	return (1);
}

int				main(int argc, char **argv)
{
	t_com 		com;
	t_phil		*phil;
	t_table		*table;
	t_all		*all;
	pthread_t	thread;
	int			i;

	memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		return (error());
	else
	{
		phil = init_phil(com.phil_nmb, com.meal); // error
		table = init_table(com.phil_nmb); // error
		all = init_all(&com, phil, table); // error
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_create(&(all[i].phil->thread), NULL, action, (void *)(&all[i]));
			usleep(50);
			i++;
		}
		pthread_create(&thread, NULL, phil_death, (void *)(all));
		pthread_join(thread, NULL);
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_detach(all[i].phil->thread);
			i++;
		}
	}
	return (0);
}
