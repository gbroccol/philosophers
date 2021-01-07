/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:37:36 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 17:53:47 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// void		print_eating_time()
// {


// 	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
// 	start = get_time(all);
// 	ft_putnbr_fd(start, 1);
// 	write(1, "ms ", 3);
// 	write(1, all->phil->name, 1);
// 	write(1, " has taken a fork\n", 18);
// 	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
// }

int			eating(t_all *all)
{
	long int	start;
	long int	finish;

	pthread_mutex_lock(&all->table->mutex[all->phil->right]);
	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->phil->name, 1);
		write(1, " has taken a fork\n", 18);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
	}

	pthread_mutex_lock(&all->table->mutex[all->phil->left]);
	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
		pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->phil->name, 1);
		write(1, " has taken a fork\n", 18);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
	}

	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
		pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->phil->name, 1);
		write(1, " is eating\n", 11);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

		start = get_time(all);
		finish = start;
		all->phil->last_meal = start;
		while ((finish - start) < all->com->time_eat)
		{
			usleep(1);
			finish = get_time(all);
		}
	}
	pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
	pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
	return (0);
}
