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
	pthread_t		*thread;

	i = 0;
	if ((phil = (t_phil *)malloc(sizeof(t_phil) * phil_nmb)) == NULL)
		return (NULL);
	if ((thread = (pthread_t *)malloc(sizeof(pthread_t) * phil_nmb)) == NULL)
		return (NULL);
	while (i < phil_nmb)
	{
		phil[i].nmb = i + 1;
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
 
t_table *init_table(int phil_nmb)
{
	int i;
	t_table *table;
	pthread_mutex_t		*mutex;

	table = NULL;
	if ((table = (t_table *)malloc(sizeof(t_table))) == NULL)
		return (NULL);
	if ((mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * phil_nmb)) == NULL)
		return (NULL);
	i = 0;
	while(i < phil_nmb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	table->mutex = mutex;
	return (table);
}

t_all		*init_all(t_com *com, t_phil *phil, t_table *table)
{
	t_all	*all;
	int		i;

	if ((all = (t_all *)malloc(sizeof(t_all) * com->phil_nmb)) == NULL)
		return (NULL);
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
    // philosopher_args_t *arg = (philosopher_args_t*) args;

	t_all *all = (t_all *)args;

    // const philosopher_t *philosopher = arg->philosopher;
    // const table_t *table = arg->table;
 
    printf("%d started dinner\n", all->phil->nmb);
 
    // pthread_mutex_lock(&table->forks[philosopher->left_fork]);
    // pthread_mutex_lock(&table->forks[philosopher->right_fork]);
 
    // printf("%s is eating\n", philosopher->name);
 
    // pthread_mutex_unlock(&table->forks[philosopher->right_fork]);
    // pthread_mutex_unlock(&table->forks[philosopher->left_fork]);
 
    // printf("%s finished dinner\n", philosopher->name);
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_com 		com;
	t_phil		*phil;
	t_table		*table;
	t_all		*all;
	int		i;

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
		while (i < com.phil_nmb)
		{
			pthread_create(all[i].phil->thread, NULL, eat, (void *)(&all[i]));
			i++;
		}
		i = 0;
		while (i < com.phil_nmb)
		{
			pthread_join(all[i].phil->thread[i], NULL);
			i++;
		}
		// wait();
		// usleep(10000);
	}
// 	timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

	return (0);
}
