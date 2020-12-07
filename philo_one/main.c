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
		if (i == 1 && (com->phil_nmb = ft_atoi(argv[1]) < 2))
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

int			main(int argc, char **argv)
{
	t_com	com;

	ft_memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		error();




	return (0);
}
