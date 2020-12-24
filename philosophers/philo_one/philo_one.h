/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:51:15 by gbroccol          #+#    #+#             */
/*   Updated: 2020/12/07 12:51:16 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h> // delete
#include <unistd.h>

typedef struct	s_com
{
	int			phil_nmb;
    int			time_die;
	int			time_eat;
	int			time_sleep;
	int			meal_nmb;
}				t_com;




/*
** libft
*/
void			*ft_memset(void *s, int c, size_t n);
int				ft_atoi(const char *str);




#endif
