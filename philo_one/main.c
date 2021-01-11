/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 17:10:45 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				error_arg(void)
{
	write(1, "Error\nWrong arguments\n", 22);
	return (1);
}

int				error_fatal(void)
{
	write(1, "Error fatal\n", 12);
	return (1);
}

void			threads_launch(t_all *all, t_com *com)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < com->phil_nmb)
	{
		pthread_create(&(all[i].phil->thread), NULL, action, (void *)(&all[i]));
		usleep(50);
		i++;
	}
	pthread_create(&thread, NULL, phil_die, (void *)(all));
	pthread_join(thread, NULL);
	i = 0;
	while (i < com->phil_nmb)
	{
		pthread_detach(all[i].phil->thread);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_com		com;
	t_all		*all;

	memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		return (error_arg());
	else
	{
		if ((all = init_all(&com)) == NULL)
			return (error_fatal());
		threads_launch(all, &com);
	}
	return (0);
}
