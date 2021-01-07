/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:37:36 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/07 21:14:20 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

	// sem_post(sem_id); // unlock
	// sem_wait(sem_id); // lock

	// sem_post(sem_print_id); // unlock
	// sem_wait(all->table->sem_print_id); // lock


// void		print_eating_time()
// {


// 	sem_wait(all->table->sem_print_id);
// 	start = get_time(all);
// 	ft_putnbr_fd(start, 1);
// 	write(1, "ms ", 3);
// 	ft_putnbr_fd(all->phil->nmb, 1);
// 	write(1, " has taken a fork\n", 18);
// 	sem_wait(all->table->sem_print_id);
// }

int			eating(t_all *all)
{
	long int	start;
	long int	finish;

	sem_wait(all->table->sem_id);
	
	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		sem_post(all->table->sem_id);
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print_id);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->phil->nmb, 1);
		write(1, " has taken a fork\n", 18);
		sem_post(all->table->sem_print_id);
	}

	sem_wait(all->table->sem_id);
	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		sem_post(all->table->sem_id);
		sem_post(all->table->sem_id);
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print_id);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->phil->nmb, 1);
		write(1, " has taken a fork\n", 18);
		sem_post(all->table->sem_print_id);
	}

	start = get_time(all);
	if ((start - all->phil->last_meal) > all->com->time_die)
	{
		sem_post(all->table->sem_id);
		sem_post(all->table->sem_id);
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print_id);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->phil->nmb, 1);
		write(1, " is eating\n", 11);
		sem_post(all->table->sem_print_id);

		start = get_time(all);
		finish = start;
		all->phil->last_meal = start;
		while ((finish - start) < all->com->time_eat)
		{
			usleep(1);
			finish = get_time(all);
		}
	}
	sem_post(all->table->sem_id);
	sem_post(all->table->sem_id);
	return (0);
}
