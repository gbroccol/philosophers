/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:45:45 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/03 20:45:52 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				thinking(t_all *all)
{
	long int		start;

	pthread_mutex_lock(&all->table->mutex[all->com->phil_nmb]);
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	write(1, all->phil->name, 1); // change
	write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&all->table->mutex[all->com->phil_nmb]);
}