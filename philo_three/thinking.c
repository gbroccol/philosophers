/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:45:45 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 15:44:54 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				thinking(t_all *all)
{
	long int		start;

	sem_wait(all->table->sem_print_id);
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->phil->nmb, 1);
	write(1, " is thinking\n", 13);
	sem_post(all->table->sem_print_id);
	return (0);
}
