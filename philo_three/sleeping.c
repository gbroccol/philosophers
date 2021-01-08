/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:44:13 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/08 13:50:18 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		sleeping(t_all *all)
{
	long int			start;
	long int			finish;

	sem_wait(all->table->sem_print_id);
	start = get_time(all);
	if (all->phil->death == 1 || (start - all->phil->last_meal) > all->com->time_die)
	{
		sem_post(all->table->sem_print_id);
		return (1);
	}
	else
	{
		ft_putnbr_fd(start, 1);
				// write(1, ">>>", 3);
		
		write(1, "ms ", 3);
		ft_putnbr_fd(all->phil->nmb, 1); // change
		write(1, " is sleeping\n", 13);
		sem_post(all->table->sem_print_id);
		start = get_time(all);
		finish = start;
		while ((finish = get_time(all)) - start < all->com->time_sleep)
			usleep(1);
	}
	return (0);
}
