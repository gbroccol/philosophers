/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 00:37:12 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/08 13:50:18 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);	
}

// static int		ft_count_int(int n)
// {
// 	int			i;
// 	int			negativ;

// 	i = 0;
// 	negativ = 0;
// 	if (n == -2147483648)
// 		return (11);
// 	if (n == 0)
// 		return (1);
// 	if (n < 0)
// 	{
// 		negativ = 1;
// 		n = n * (-1);
// 	}
// 	while (n != 0)
// 	{
// 		n = n / 10;
// 		i++;
// 	}
// 	return (negativ ? (i + 1) : i);
// }

// char		*ft_itoa(int n)
// {
// 	char	*res;
// 	int		count;
// 	int		negativ;

// 	negativ = 0;
// 	if (n < 0)
// 		negativ = 1;
// 	count = ft_count_int(n);
// 	if ((res = malloc((count + 1) * sizeof(char))) == NULL)
// 		return (NULL);
// 	res[count] = '\0';
// 	if (n == -2147483648)
// 		res[--count] = '8';
// 	if (n == -2147483648)
// 		n = -214748364;
// 	if (negativ == 1)
// 		n = n * (-1);
// 	while (count)
// 	{
// 		res[--count] = ((char)(n % 10 + '0'));
// 		n = n / 10;
// 	}
// 	if (negativ == 1)
// 		res[0] = '-';
// 	return (res);
// }

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
