/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:05:24 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 16:06:07 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_phil				*init_phil(int phil_nmb, int meal)
{
	int				i;
	t_phil			*phil;

	i = 0;
	if ((phil = (t_phil *)malloc(sizeof(t_phil) * phil_nmb)) == NULL)
		return (NULL);
	while (i < phil_nmb)
	{
		phil[i].last_meal = 0;
		phil[i].death = 0;
		phil[i].meal_count = meal;
		phil[i].nmb = i + 1;
		i++;
	}
	return (phil);
}

t_table				*init_table(int phil_nmb)
{
	t_table			*table;
	sem_t			*sem_id;
	sem_t			*sem_print_id;

	table = NULL;
	if ((table = (t_table *)malloc(sizeof(t_table))) == NULL)
		return (NULL);
	if (sem_unlink("sem_id") == -1)
		return (NULL);
	if ((sem_id = sem_open("sem_id", O_CREAT, 0666, phil_nmb)) == SEM_FAILED)
		return (NULL);
	table->sem_id = sem_id;
	if (sem_unlink("sem_print_id") == -1)
		return (NULL);
	if ((sem_print_id = sem_open("sem_print_id", O_CREAT, 0666, 1))
			== SEM_FAILED)
		return (NULL);
	table->sem_print_id = sem_print_id;
	return (table);
}

t_all				*init_all(t_com *com)
{
	t_phil			*phil;
	t_table			*table;
	t_all			*all;
	struct timeval	tv;
	int				i;

	if ((phil = init_phil(com->phil_nmb, com->meal)) == NULL)
		return (NULL);
	if ((table = init_table(com->phil_nmb)) == NULL)
		return (NULL);
	if ((all = (t_all *)malloc(sizeof(t_all) * com->phil_nmb)) == NULL)
		return (0);
	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	com->start_time_ms = (unsigned int)((tv.tv_sec) * 1000 +
			(tv.tv_usec) / 1000);
	i = 0;
	while (i < com->phil_nmb)
	{
		all[i].com = com;
		all[i].table = table;
		all[i].phil = &phil[i];
		i++;
	}
	return (all);
}
