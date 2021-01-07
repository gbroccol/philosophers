/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:28 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 20:24:42 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*action(void *args)
{
	t_all			*all;
	struct timeval	tv;

	all = (t_all *)args;
	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	while (all->phil->meal_count != 0)
	{
		if (all->phil->meal_count == -1 || all->phil->meal_count > 0)
		{
			if (eating(all) == 1 || sleeping(all) == 1 || thinking(all) == 1)
				return (NULL);
			if (all->phil->meal_count > 0)
				all->phil->meal_count--;
		}
	}
	return (NULL);
}
