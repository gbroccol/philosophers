/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2020/12/29 16:31:16 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
0 ...
1 number_of_philosophers
2 time_to_die 
3 time_to_eat
4 time_to_sleep 
5 [number_of_times_each_philosopher_must_eat]
*/

void		eating(t_all *all)
{
	long int			finish;
	long int			start;

	pthread_mutex_lock(&all->table->mutex[all->phil->right]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	write(1, all->phil->name, 1);
	write(1, " has taken a right fork\n", 24); // rm right
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	pthread_mutex_lock(&all->table->mutex[all->phil->left]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	write(1, all->phil->name, 1);
	write(1, " has taken a left fork\n", 23); // rm left
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]); // add extra thread
	write(1, all->phil->name, 1);
	write(1, " is eating\n", 11);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	start = get_time();
	finish = start;
	while ((finish = get_time()) - start < all->com->time_sleep)
		usleep(1);
	
	all->phil->start = finish;
	
	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	ft_putnbr_fd((finish - start), 1);
	write(1, "   <-- eat\n", 11);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
	
	pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
	pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
	usleep(50);
}

void		sleeping(t_all *all)
{
	long int			start;
	long int			finish;

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	write(1, all->phil->name, 1); // change
	write(1, " is sleeping\n", 13);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);

	start = get_time();
	finish = start;
	while ((finish = get_time()) - start < all->com->time_sleep)
		usleep(1);
	
	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	ft_putnbr_fd((finish - start), 1);
	write(1, "   <-- sleep\n", 13);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
}

void		thinking(t_all *all)
{
	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	write(1, all->phil->name, 1); // change
	write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
}

void	*action(void *args)
{
	t_all *all = (t_all *)args;
	struct		timeval tv;
	// int i = 0;

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	all->phil->start = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	
// time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

	while (all->die == 0)
	{
		eating(all);
		sleeping(all);
		thinking(all);
		// usleep(50);
	}
	return (NULL);
}

// 	timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died


int				main(int argc, char **argv)
{
	t_com 		com;
	t_phil		*phil;
	t_table		*table;
	t_all		*all;
	pthread_t			thread;
	unsigned int		i;

	memset(&com, 0, sizeof(t_com));
	// memset(&all, 0, sizeof(t_all));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		error();
	else
	{
		phil = init_phil(com.phil_nmb);
		table = init_table(com.phil_nmb);
		all = init_all(&com, phil, table); // error
		i = 0;

		// eat((void *)(&all[0]));
		// eat((void *)(&all[1]));
		// eat((void *)(&all[2]));
		// eat((void *)(&all[3]));
		// eat((void *)(&all[4]));
		// eat((void *)(&all[5]));

		while (i < com.phil_nmb)
		{
			// printf("phil %d\n", all[i].phil->nmb);
			pthread_create(&(all[i].phil->thread), NULL, action, (void *)(&all[i]));
			usleep(50);
			i++;
		}

		// all->thread = (pthread_t)malloc(sizeof(pthread_t));

		// phil_die((void *)(&all[i]));

		pthread_create(&thread, NULL, phil_die, (void *)(&all[0]));
		pthread_join(thread, NULL);
		
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_join(&(all[i].phil->thread[i]), NULL);
			// pthread_detach(&(all[i].phil->thread[i]));
			i++;
		}
		// wait();
		// usleep(10000);
	}
	return (0);
}
