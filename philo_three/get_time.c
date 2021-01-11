/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:38:52 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 16:14:53 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long int			get_time(t_all *all)
{
	long int		finish;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	finish = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (finish - all->com->start_time_ms);
}
