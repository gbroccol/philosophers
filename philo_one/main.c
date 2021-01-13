/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 18:15:17 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			free_all(t_all *all)
{
	if (all->phil != NULL)
		free(all->phil);
	if (all->table != NULL)
		free(all->table);
	if (all->table->mutex != NULL)
		free(all->table->mutex);
	if (all != NULL)
		free(all);
}

int				error_arg(void)
{
	write(2, "Error\nWrong arguments\n", 22);
	return (1);
}

int				error_fatal(t_all *all)
{
	write(2, "Error fatal\n", 12);
	free_all(all);
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
		all = NULL;
		if ((all = init_all(&com)) == NULL)
			return (error_fatal(all));
		threads_launch(all, &com);
	}
	free_all(all);
	return (0);
}
