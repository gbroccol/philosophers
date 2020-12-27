/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2020/12/07 12:53:50 by gbroccol         ###   ########.fr       */
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

void		error()
{
	write(1, "Error\nBad arguments\n", 20);
}

int			ft_is_wrong_smb(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int			pars_args(t_com *com, char **argv)
{
	int		i;

	i = 1;
	com->meal_nmb = -1;
	while (argv[i] != NULL)
	{
		if (ft_is_wrong_smb(argv[i]))
			return (1);
		if (i == 1 && (com->phil_nmb = ft_atoi(argv[1])) < 2)
			return (1);
		else if (i == 2 && (com->time_die = ft_atoi(argv[2])) < 0)
			return (1);
		else if (i == 3 && (com->time_eat = ft_atoi(argv[3])) < 0)
			return (1);
		else if (i == 4 && (com->time_sleep = ft_atoi(argv[4])) < 0)
			return (1);
		else if (i == 5 && (com->meal_nmb = ft_atoi(argv[5])) < 0)
			return (1);
		i++;
	}
	return (0);
}

t_phil *init_phil(int phil_nmb)
{
	int				i;
	t_phil			*phil;

	i = 0;
	if ((phil = (t_phil *)malloc(sizeof(t_phil) * phil_nmb)) == NULL)
		return (NULL);
	while (i < phil_nmb)
	{
		phil[i].nmb = i + 1;
		phil[i].name = ft_itoa(phil[i].nmb);
		phil[i].right = i;
		if ((phil_nmb - 1) == i)
			phil[i].left = 0;
		else
			phil[i].left = i + 1;
		// printf("Phil %d, right %d, left %d\n", phil[i].nmb, phil[i].right, phil[i].left);
		i++;
	}
	return (phil);
}
 
t_table *init_table(unsigned int phil_nmb)
{
	unsigned int i;
	t_table *table;
	pthread_mutex_t		*mutex;

	table = NULL;
	if ((table = (t_table *)malloc(sizeof(t_table))) == NULL)
		return (NULL);
	if ((mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (phil_nmb + 1))) == NULL)
		return (NULL);
	i = 0;
	while(i < phil_nmb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex[i], NULL);
	table->mutex = mutex;
	return (table);
}

t_all *init_all(t_com *com, t_phil *phil, t_table *table)
{
	t_all	*all;
	unsigned int		i;

	if ((all = (t_all *)malloc(sizeof(t_all) * com->phil_nmb)) == NULL)
		return (0);
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

void	*eat(void *args)
{
	t_all *all = (t_all *)args;
	struct		timeval tv;
	int i = 0;

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	all->phil->start = (unsigned int)(tv.tv_usec - all->phil->start);
	// printf("--------------------------->>>>start micro seconds : %d\n", all->phil->start);


    // philosopher_args_t *arg = (philosopher_args_t*) args;

    // const philosopher_t *philosopher = arg->philosopher;
    // const table_t *table = arg->table;
	//   [philosopher->left_fork]

	while (i < 7)
	{
		
	
		pthread_mutex_lock(&all->table->mutex[all->phil->right]);


		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		write(1, all->phil->name, 1);
		write(1, " has taken a right fork\n", 24); // rm right
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		// usleep(50);

		pthread_mutex_lock(&all->table->mutex[all->phil->left]);

		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		write(1, all->phil->name, 1);
		write(1, " has taken a left fork\n", 23); // rm left
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		// usleep(50);


		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]); // add extra thread
		write(1, all->phil->name, 1);
		write(1, " is eating\n", 11);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		
		// eating
		while ((all->phil->finish - all->phil->start) < all->com->time_eat)
		{
			if (gettimeofday(&tv, NULL) == -1)
				return (NULL);
			all->phil->finish = (unsigned int)(tv.tv_usec - all->phil->start);
		}
		
		// new start time
		// all->phil->start = (unsigned int)(tv.tv_usec - all->phil->start);
		all->phil->start = all->phil->finish;
		
		
		
		// usleep(50);

		// while (all->com->time_eat > time_to_action)
		// {
		// 	if (gettimeofday(&tv, NULL) == -1)
		// 		return (NULL);
		// 	time_to_action = (unsigned int)(tv.tv_usec - all->phil->start);
		// 	// time_to_action = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
		// 	printf("-------------%d-------------->>>>time to action micro seconds : %d\n", all->phil->nmb, time_to_action);
		// }

		// while (i < 7)
		// {
		// 	if (gettimeofday(&tv, NULL) == -1)
		// 		return (NULL);
		// 	time_to_action = (unsigned int)(tv.tv_usec - all->phil->start);
		// 	printf("-------%d-------->>>>time to action micro seconds : %ld\n", all->phil->nmb, time_to_action);
		// 	i++;
		// }
		

		// printf("-------------%d-------------->>>>finish eating micro seconds : %d\n", all->phil->nmb, tv.tv_usec);
		// printf("-------------%d-------------->>>>time to action micro seconds : %d\n", all->phil->nmb, time_to_action);

		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		write(1, all->phil->name, 1);
		write(1, " is sleeping\n", 13);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		// usleep(50);

		pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
		write(1, all->phil->name, 1);
		write(1, " is thinking\n", 13);
		pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
		// usleep(50);

		usleep(40000);

		pthread_mutex_unlock(&all->table->mutex[all->phil->left]);
		pthread_mutex_unlock(&all->table->mutex[all->phil->right]);
	
    // printf("%d finished dinner\n", all->phil->nmb);
	
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
			pthread_create(&(all[i].phil->thread), NULL, eat, (void *)(&all[i]));
			usleep(50);
			i++;
		}
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_join(&(all[i].phil->thread[i]), NULL);
			i++;
		}
		// wait();
		// usleep(10000);
	}


	return (0);
}
