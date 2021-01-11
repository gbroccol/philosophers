/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_death.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 15:48:06 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			*phil_death(void *args)
{
	long int	finish;
	t_all		*all;

	all = (t_all *)args;
	while (1)
	{
		finish = get_time(all);
		if ((finish - all->phil->last_meal) > all->com->time_die)
		{
			if (all->phil->meal_count != 0)
			{
				sem_wait(all->table->sem_print_id);
				ft_putnbr_fd(finish, 1);
				write(1, "ms ", 3);
				ft_putnbr_fd(all->phil->nmb, 1);
				write(1, " died\n", 6);
				exit(1);
			}
			else
				exit(2);
		}
		usleep(10);
	}
	return (NULL);
}
