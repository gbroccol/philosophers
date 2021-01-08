/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:49 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/08 15:44:44 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		error()
{
	write(1, "Error\nWrong arguments\n", 22);
	return (1);
}

// fork, kill, exit, waitpid

int				main(int argc, char **argv)
{
	// pid_t pid_death;
	t_com 		com;
	t_phil		*phil;
	t_table		*table;
	t_all		*all;
	// pthread_t	thread;
	int			i;

	memset(&com, 0, sizeof(t_com));
	if (argc < 5 || argc > 6 || pars_args(&com, argv))
		return (error());
	else
	{
		phil = init_phil(com.phil_nmb, com.meal); // error
		table = init_table(com.phil_nmb); // error
		all = init_all(&com, phil, table); // error
		i = 0;
		while (i < com.phil_nmb)
		{
			all[i].phil->pid = fork();
			if (all[i].phil->pid == 0) // child
			{
				action((void *)(&all[i]));
				if (all->phil->meal_count == 0)
					exit(0); // he is full
				else
					exit (1); // dead
			}
			else if (all[i].phil->pid == -1) // errror
			{
				write(2, "error: fatal\n", 13);
				exit(1);
			}
			i++;
		}
		// pid_death = fork();
		// if (pid_death == 0) // child
		// {
		// 	// phil_death((void *)(all));
		// 	// action((void *)(&all[i]));
		// 	// if (all->phil->meal_count == 0)
		// 	// 	exit(0); // he is full
		// 	// else
		// 	// 	exit (1); // dead
		// 	exit (0);
		// }
		// else if (all[i].phil->pid == -1) // errror
		// {
		// 	write(2, "error: fatal\n", 13);
		// 	exit(1);
		// }


		

		
		i = 0;
		while (i < com.phil_nmb)
		{
			waitpid(all[i].phil->pid, &all[i].phil->status, WUNTRACED);
			while (!WIFEXITED(all[i].phil->status) && !WIFSIGNALED(all[i].phil->status))
				waitpid(all[i].phil->pid, &all[i].phil->status, WUNTRACED);
			// return_value = WEXITSTATUS(&all[i].phil->status);
			i++;
		}
		
		// pthread_create(&thread, NULL, phil_death, (void *)(all));
		// pthread_join(thread, NULL);
		// i = 0;
		// while (i < com.phil_nmb)
		// {
		// 	// pthread_detach(all[i].phil->thread);
		// 	i++;
		// }
	}
	return (0);
}
