/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 17:48:33 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		set_death(t_all *all)
{
	int		i;

	i = 0;
	while (i < all[0].com->phil_nmb)
	{
		all[i].phil->death = 1;
		i++;
	}
}

int			check_phil_is_full(t_all *all)
{
	int		i;

	i = 0;
	while (i < all[0].com->phil_nmb)
	{
		if (all[i].phil->meal_count > 0)
			return (0);
		i++;
	}
	return (1);
}

void			*phil_die(void *args)
{
	int			i;
	long int	finish;
	t_all		*all = (t_all *)args;

	while (1)
	{
		i = 0;
		finish = get_time(all);
		while (i < all[0].com->phil_nmb)
		{
			if ((finish - all[i].phil->last_meal) > all->com->time_die)
			{
				if (all[i].phil->meal_count != 0)
				{
					pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
					ft_putnbr_fd(finish, 1);
					write(1, "ms ", 3);
					write(1, all[i].phil->name, ft_strlen(all[i].phil->name));
					write(1, " died\n", 6);
					set_death(all);
					pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
				}
				if (all[i].phil->meal_count == -1 || (all[i].phil->meal_count == 0 && check_phil_is_full(all) == 1))
					return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
