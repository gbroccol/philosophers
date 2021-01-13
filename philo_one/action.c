/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:28 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 16:22:58 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static long int		print_action(t_all *all, char *text, int phil)
{
	long int		start;

	start = -1;
	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	if (all->phil->death == 0)
	{
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(phil, 1);
		write(1, text, ft_strlen(text));
	}
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
	return (start);
}

static void			sleeping(t_all *all)
{
	long int		start;

	start = print_action(all, " is sleeping\n", all->phil->nmb);
	if (start != -1)
	{
		while ((get_time(all) - start) < all->com->time_sleep)
			usleep(1);
	}
}

static void			eating(t_all *all)
{
	long int		start;

	pthread_mutex_lock(&all->table->mutex[all->phil->right]);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	pthread_mutex_lock(&all->table->mutex[all->phil->left]);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	start = print_action(all, " is eating\n", all->phil->nmb);
	if (start != -1)
	{
		all->phil->last_meal = start;
		while ((get_time(all) - start) < all->com->time_eat)
			usleep(1);
	}
	pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
	pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
}

void				*action(void *args)
{
	t_all			*all;
	struct timeval	tv;

	all = (t_all *)args;
	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	while (all->phil->meal_count != 0)
	{
		if (all->phil->meal_count == -1 || all->phil->meal_count > 0)
		{
			eating(all);
			sleeping(all);
			print_action(all, " is thinking\n", all->phil->nmb);
			if (all->phil->meal_count > 0)
				all->phil->meal_count--;
			usleep(50);
		}
	}
	return (NULL);
}
