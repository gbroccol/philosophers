/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:10:54 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 17:51:16 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_phil					*init_phil(int phil_nmb, int meal)
{
	int					i;
	t_phil				*phil;

	i = 0;
	if ((phil = (t_phil *)malloc(sizeof(t_phil) * phil_nmb)) == NULL)
		return (NULL);
	while (i < phil_nmb)
	{
		phil[i].last_meal = 0;
		phil[i].death = 0;
		phil[i].meal_count = meal;
		phil[i].nmb = i + 1;
		phil[i].right = i;
		if ((phil_nmb - 1) == i)
			phil[i].left = 0;
		else
			phil[i].left = i + 1;
		i++;
	}
	return (phil);
}

t_table					*init_table(int phil_nmb)
{
	int					i;
	t_table				*table;
	pthread_mutex_t		*mutex;

	table = NULL;
	if ((table = (t_table *)malloc(sizeof(t_table))) == NULL)
		return (NULL);
	if ((mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
		(phil_nmb + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < phil_nmb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex[i], NULL);
	table->mutex = mutex;
	return (table);
}

t_all					*init_all(t_com *com)
{
	t_phil				*phil;
	t_table				*table;
	t_all				*all;
	struct timeval		tv;
	int					i;

	if ((phil = init_phil(com->phil_nmb, com->meal)) == NULL)
		return (NULL);
	if ((table = init_table(com->phil_nmb)) == NULL)
		return (NULL);
	if ((all = (t_all *)malloc(sizeof(t_all) * com->phil_nmb)) == NULL)
		return (NULL);
	i = 0;
	while (i < com->phil_nmb)
	{
		if (gettimeofday(&tv, NULL) == -1)
			return (NULL);
		all[i].start_time_ms = (unsigned int)((tv.tv_sec) *
				1000 + (tv.tv_usec) / 1000);
		all[i].com = com;
		all[i].table = table;
		all[i].phil = &phil[i];
		i++;
	}
	return (all);
}
