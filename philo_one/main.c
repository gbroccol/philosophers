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

void init_phil(t_phil *phil, int phil_nmb)
{
	int i;

	i = 0;
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
}
 
void init_table(t_table *table, int phil_nmb)
{
    int i;

	i = 0;
	while(i < phil_nmb)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

// void print_phil(t_all *all)
// {
// 	int i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		printf("______________\n");
// 		printf("Phil %d, right %d, left %d\n", all->phil[i].nmb, all->phil[i].right, all->phil[i].left);
// 		i++;
// 	}
// }

int			main(int argc, char **argv)
{
	t_com 	com;
	t_all	all;

	memset(&com, 0, sizeof(t_com));
	memset(&all, 0, sizeof(t_all));
	// memset(all.phil, 0, sizeof(t_phil));
	// memset(all.table, 0, sizeof(t_table));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		error();
	else
	{
		// printf("_______%d_______\n", com.phil_nmb);
		if ((all.phil = (t_phil *)malloc(sizeof(t_phil) * com.phil_nmb)) == NULL)
			return (1);
		init_phil(all.phil, com.phil_nmb);
		// init_table(all.table, com.phil_nmb);

		// print_phil(&all);
	}
	
// 	timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

	return (0);
}
