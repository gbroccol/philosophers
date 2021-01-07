/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:44:13 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 17:35:32 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		sleeping(t_all *all)
{
	long int			start;
	long int			finish;

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	start = get_time(all);
	if (all->phil->death == 1 || (start - all->phil->last_meal) > all->com->time_die)
	{
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		return (1);
	}
	else
	{
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->phil->name, 1); // change
		write(1, " is sleeping\n", 13);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		start = get_time(all);
		finish = start;
		while ((finish = get_time(all)) - start < all->com->time_sleep)
			usleep(1);
	}
	return (0);
}