/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 00:37:12 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 18:07:02 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int				ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			minus;

	i = 0;
	res = 0;
	minus = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		minus = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > ((res * 10) + (str[i] - '0')) && minus == 1)
			return (0);
		else if (res > ((res * 10) + (str[i] - '0')) && minus == 0)
			return (-1);
		else
			res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (minus ? -res : res);
}
