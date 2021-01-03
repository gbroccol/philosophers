/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:37:36 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/03 20:40:58 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			eating(t_all *all)
{
	long int	finish;
	long int	start;

	pthread_mutex_lock(&all->table->mutex[all->phil->right]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	start = get_time(all); // ???
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	write(1, all->phil->name, 1);
	write(1, " has taken a fork\n", 18);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	pthread_mutex_lock(&all->table->mutex[all->phil->left]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	start = get_time(all); // ???
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	write(1, all->phil->name, 1);
	write(1, " has taken a fork\n", 18);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	// pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	// write(1, all->phil->name, 1);
	// write(1, " has taken a left fork\n", 23); // rm left
	// pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]); // add extra thread
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	write(1, all->phil->name, 1);
	write(1, " is eating\n", 11);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	start = get_time(all);
	finish = start;
	while ((finish - start) < all->com->time_eat)
	{
		usleep(1);
		finish = get_time(all);
	}
	all->phil->start = get_time(all);
	
	pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
	pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
	usleep(50);
}