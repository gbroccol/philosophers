/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:28 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 16:14:30 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*action(void *args)
{
	t_all			*all;
	pthread_t		thread;

	all = (t_all *)args;
	pthread_create(&thread, NULL, phil_death, (void *)(all));
	while (all->phil->meal_count != 0)
	{
		if (all->phil->meal_count == -1 || all->phil->meal_count > 0)
		{
			if (eating(all) == 1 || sleeping(all) == 1 || thinking(all) == 1)
				break ;
			if (all->phil->meal_count > 0)
				all->phil->meal_count--;
		}
	}
	pthread_join(thread, NULL);
	return (NULL);
}
