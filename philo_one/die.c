/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:01:30 by gbroccol          #+#    #+#             */
/*   Updated: 2020/12/29 16:34:39 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);	
}

long int get_time()
{
	long int finish;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	finish = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (finish);
}


void *phil_die(void *args)
{
	unsigned int	i;
	long int		finish;
	t_all			*all = (t_all *)args;

	while (1)
	{
		i = 0;
		while (i < all->com->phil_nmb)
		{
			finish = get_time();

			// pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
			// ft_putnbr_fd(all->phil->start, 1);
			// write(1, "\t", 1);
			// pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
			
			if ((finish - all->phil->start) > all->com->time_die)
			{
				all->die = 1;
				ft_putnbr_fd((finish - all->phil->start), 1);
				write(1, "\t", 1);
				
				pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
				write(1, all[i].phil->name, ft_strlen(all[i].phil->name));
				pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
				
				write(1, " died\n", 6);
				// exit (1);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}