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

void			*phil_die(void *args)
{
	int			i;
	long int	finish;
	t_all		*all = (t_all *)args;

	while (1)
	{
		// i = 0;
		// if (all->com->meal_nmb != -1)
		// {
		// 	i = 0;
		// 	count = 0;
		// 	while (i < all->com->phil_nmb)
		// 	{
		// 		if (all[i].com->meal_nmb == 0)
		// 			count++;
		// 		i++;	
		// 	}
		// 	if (count == all->com->phil_nmb)
		// 		break ;
		// }
		i = 0;
		finish = get_time(all);
		while (i < all[0].com->phil_nmb)
		{
			if ((finish - all[i].phil->last_meal) > all->com->time_die)
			{
				pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
				ft_putnbr_fd(finish, 1);
				write(1, "ms ", 3);
				write(1, all[i].phil->name, ft_strlen(all[i].phil->name));
				write(1, " died\n", 6);
				set_death();
				pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
				return (NULL);
			}



			// if (i < all->com->phil_nmb && all[i].com->meal_nmb == 0)
			// {
			// 	i++;
			// 	continue ;
			// }
			// else if ((finish - all->phil->last_meal) > all->com->time_die)
			// {
			// 	j = 0;
			// 	while (j < all->com->phil_nmb)
			// 	{
			// 		all[j].die = 1;
			// 		j++;
			// 	}
				// ft_putnbr_fd((finish - all->phil->last_meal), 1);
				// write(1, "ms ", 3);
				
				// pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
				// write(1, all[i].phil->name, ft_strlen(all[i].phil->name));
				// write(1, " died\n", 6);
				// pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
				
				
			// 	return (NULL);
			// }
			i++;
		}
	}
	return (NULL);
}
