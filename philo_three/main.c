/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:38 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				error(void)
{
	write(2, "Error\nWrong arguments\n", 22);
	return (-1);
}

void			kill_all(t_all *all)
{
	int			i;

	i = 0;
	while (i < all->com->phil_nmb)
	{
		kill(all[i].phil->pid, SIGKILL);
		i++;
	}
}

int				wait_children(t_all *all)
{
	int			return_value;
	int			count;
	int			status;

	return_value = 0;
	count = 0;
	while (count < all->com->phil_nmb)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return_value = WEXITSTATUS(status);
		if (return_value == 1 || return_value == -1)
		{
			kill_all(all);
			if (return_value == -1)
				return (-1);
			exit(0);
		}
		count++;
	}
	return (0);
}

int				launch_children(t_all *all)
{
	int			i;

	i = 0;
	while (i < all->com->phil_nmb)
	{
		all[i].phil->pid = fork();
		if (all[i].phil->pid == 0)
		{
			usleep(50);
			action((void *)(&all[i]));
		}
		else if (all[i].phil->pid == -1)
		{
			kill_all(all);
			return (-1);
		}
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_com		com;
	t_all		*all;

	memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		return (error());
	else
	{
		if ((all = init_all(&com)) == NULL)
			return (error());
		if (launch_children(all) == -1 || wait_children(all) == -1)
		{
			write(2, "error: fatal\n", 13);
			return (-1);
		}
	}
	return (0);
}
