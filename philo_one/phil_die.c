/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_die.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 16:51:13 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		ft_putnbr_fd(finish, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all[i].phil->nmb, 1);
		write(1, " died\n", 6);
		set_death(all);
		return (1);
	}
	if (all[i].phil->meal_count == -1 ||
		(all[i].phil->meal_count == 0 && check_phil_is_full(all) == 1))
		return (1);
	return (0);
}

void			*phil_die(void *args)
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
				if (check_death(all, i, finish))
					return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
