/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 17:03:21 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			set_death(t_all *all)
{
	int			i;

	i = 0;
	while (i < all[0].com->phil_nmb)
	{
		all[i].phil->death = 1;
		i++;
	}
}

int				check_phil_is_full(t_all *all)
{
	int			i;

	i = 0;
	while (i < all[0].com->phil_nmb)
	{
		if (all[i].phil->meal_count > 0)
			return (0);
		i++;
	}
	return (1);
}

int				check_death(t_all *all, int i, long int finish)
{
	if (all[i].phil->meal_count != 0)
	{
		sem_wait(all->table->sem_print_id);
		if ((finish - all[i].phil->last_meal) > all->com->time_die)
		{
			ft_putnbr_fd(finish, 1);
			write(1, "ms ", 3);
			ft_putnbr_fd(all[i].phil->nmb, 1);
			write(1, " died\n", 6);
			set_death(all);
			sem_post(all->table->sem_print_id);
			return (1);
		}
		sem_post(all->table->sem_print_id);
		return (0);
	}
	if (all[i].phil->meal_count == 0 && check_phil_is_full(all) == 1)
		return (1);
	return (0);
}

void			*phil_death(void *args)
{
	int			i;
	long int	finish;
	t_all		*all;

	all = (t_all *)args;
	while (1)
	{
		i = 0;
		finish = get_time(all);
		while (i < all[0].com->phil_nmb)
		{
			if ((finish - all[i].phil->last_meal) > all->com->time_die)
			{
				if (check_death(all, i, finish) == 1)
					return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
