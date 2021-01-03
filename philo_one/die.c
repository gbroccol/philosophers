/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/03 20:38:37 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *phil_die(void *args)
{
	unsigned int	i;
	unsigned int	j;
	long int		finish;
	t_all			*all = (t_all *)args;
	unsigned int	count;

	while (1)
	{
		i = 0;
		if (all->com->meal_nmb != -1)
		{
	
			i = 0;
			count = 0;
			while (i < all->com->phil_nmb)
			{
				if (all[i].com->meal_nmb == 0)
					count++;
				i++;	
			}
			if (count == all->com->phil_nmb)
				break ;
		}
		while (i < all[0].com->phil_nmb)
		{
			finish = get_time(all);
			if (i < all->com->phil_nmb && all[i].com->meal_nmb == 0)
			{
				i++;
				continue ;
			}
			else if ((finish - all->phil->start) > all->com->time_die)
			{
				j = 0;
				while (j < all->com->phil_nmb)
				{
					all[j].die = 1;
					j++;
				}
				ft_putnbr_fd((finish - all->phil->start), 1);
				write(1, "ms ", 3);
				
				pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
				write(1, all[i].phil->name, ft_strlen(all[i].phil->name));
				pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
				
				write(1, " died\n", 6);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}