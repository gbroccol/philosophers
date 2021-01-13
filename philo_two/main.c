/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/13 12:59:11 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			free_all(t_all *all)
{
	sem_unlink("sem_id");
	sem_unlink("sem_print_id");
	sem_close(all->table->sem_id);
	sem_close(all->table->sem_print_id);
	if (all->phil != NULL)
		free(all->phil);
	if (all->table != NULL)
		free(all->table);
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

int				launch_threads(t_com *com, t_all *all)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < com->phil_nmb)
	{
		pthread_create(&(all[i].phil->thread), NULL, action, (void *)(&all[i]));
		usleep(50);
		i++;
	}
	pthread_create(&thread, NULL, phil_death, (void *)(all));
	pthread_join(thread, NULL);
	i = 0;
	while (i < com->phil_nmb)
	{
		pthread_detach(all[i].phil->thread);
		i++;
	}
	return (0);
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
			return (error_fatal(all));
		if ((launch_threads(&com, all)) == -1)
			return (error_fatal(all));
	}
	free_all(all);
	return (0);
}
