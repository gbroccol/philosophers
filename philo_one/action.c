/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:28 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/03 20:47:29 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*action(void *args)
{
	t_all			*all;
	struct timeval	tv;

	all = (t_all *)args;
	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	all->phil->start = all->start_prog;
	while (all->die == 0 && all->com->meal_nmb != 0)
	{
		if (all->com->meal_nmb == -1 || all->com->meal_nmb > 0)
		{
			eating(all);
			sleeping(all);
			thinking(all);
			if (all->com->meal_nmb > 0)
				all->com->meal_nmb--;
		}
		if (all->com->meal_nmb == 0)
			break ;
	}
	return (NULL);
}