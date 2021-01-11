/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:51:15 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/11 17:17:25 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>

typedef struct			s_com
{
	long int			phil_nmb;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	long int			meal;
}						t_com;

typedef struct			s_phil
{
	long int			last_meal;
	int					meal_count;
	int					nmb;
	int					death;
	pthread_t			thread;
}						t_phil;

typedef struct			s_table
{
	sem_t				*sem_id;
	sem_t				*sem_print_id;
}						t_table;

typedef struct			s_all
{
	t_com				*com;
	t_table				*table;
	t_phil				*phil;
	long int			start_time_ms;
}						t_all;

t_phil					*init_phil(int phil_nmb, int meal);
t_table					*init_table(int phil_nmb);
t_all					*init_all(t_com *com, t_phil *phil, t_table *table);
int						pars_args(t_com *com, char **argv);
void					*action(void *args);
int						eating(t_all *all);
int						sleeping(t_all *all);
int						thinking(t_all *all);
void					*phil_death(void *args);
long int				get_time(t_all *all);

// /*
// ** libft
// */
int						ft_atoi(const char *str);
void					ft_putnbr_fd(long int n, int fd);
int						ft_strlen(char *str);

#endif
