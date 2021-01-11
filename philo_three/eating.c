/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:37:36 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 16:13:29 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			print_action(t_all *all, char *text, int phil)
{
	long int	start;

	sem_wait(all->table->sem_print_id);
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(phil, 1);
	write(1, text, ft_strlen(text));
	sem_post(all->table->sem_print_id);
}

int				eating(t_all *all)
{
	long int	start;
	long int	finish;

	sem_wait(all->table->sem_id);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	sem_wait(all->table->sem_id);
	print_action(all, " has taken a fork\n", all->phil->nmb);
	print_action(all, " is eating\n", all->phil->nmb);
	start = get_time(all);
	finish = start;
	all->phil->last_meal = start;
	while ((finish - start) < all->com->time_eat)
	{
		usleep(10);
		finish = get_time(all);
	}
	sem_post(all->table->sem_id);
	sem_post(all->table->sem_id);
	return (0);
}
