/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/12 18:05:11 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			free_all(t_all *all)
{
	if (all->phil != NULL)
		free(all->phil);
	if (all->table != NULL)
		free(all->table);
	if (all != NULL)
		free(all);
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
	{
		write(2, "Error\nWrong arguments\n", 22);
		return (1);
	}
	else
	{
		if ((all = init_all(&com)) == NULL ||
				launch_children(all) == -1 ||
				wait_children(all) == -1)
		{
			write(2, "error: fatal\n", 13);
			free_all(all);
			return (-1);
		}
	}
	free_all(all);
	return (0);
}
