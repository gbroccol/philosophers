/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:28 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 17:34:32 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long int			print_action(t_all *all, char *text, int phil)
{
	long int		start;

	start = -1;
	sem_wait(all->table->sem_print_id);
	if (all->phil->death == 0)
	{
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(phil, 1);
		write(1, text, ft_strlen(text));
	}
	sem_post(all->table->sem_print_id);
	return (start);
}

int					sleeping(t_all *all)
{
	long int		start;

	start = print_action(all, " is sleeping\n", all->phil->nmb);
	if (start != -1)
	{
		while ((get_time(all) - start) < all->com->time_sleep)
			usleep(10);
	}
	return (0);
}

int					eating(t_all *all)
{
	long int		start;

	sem_wait(all->table->sem_id);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	sem_wait(all->table->sem_id);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	start = print_action(all, " is eating\n", all->phil->nmb);
	if (start != -1)
	{
		all->phil->last_meal = start;
		while ((get_time(all) - start) < all->com->time_eat)
			usleep(10);
	}
	sem_post(all->table->sem_id);
	sem_post(all->table->sem_id);
	return (0);
}

void				*action(void *args)
{
	t_all			*all;
	pthread_t		thread;

	all = (t_all *)args;
	pthread_create(&thread, NULL, phil_death, (void *)(all));
	while (all->phil->meal_count != 0)
	{
		if (all->phil->meal_count == -1 || all->phil->meal_count > 0)
		{
			eating(all);
			sleeping(all);
			print_action(all, " is thinking\n", all->phil->nmb);
			if (all->phil->meal_count > 0)
				all->phil->meal_count--;
		}
	}
	pthread_join(thread, NULL);
	return (NULL);
}
