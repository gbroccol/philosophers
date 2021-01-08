/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:49:07 by gbroccol          #+#    #+#             */
/*   Updated: 2021/01/08 14:46:47 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

// deadlock - соблюсти очередность запуска в самом начале

// ./philo_two 4 310 200 100 SEGA


	// sem_post(all->table->sem_id); // unlock
	// sem_wait(all->table->sem_id); // lock

	// sem_post(all->table->sem_print_id); // unlock
	// sem_wait(all->table->sem_print_id); // lock


// memset, malloc, free, write

// fork, kill, exit, waitpid

// pthread_create, pthread_detach, pthread_join,

// usleep, gettimeofday, 

// sem_open - создает новый именованный семафор или открывает существующий
// sem_close
// sem_post ++
// sem_wait --
// sem_unlink - Именованный семафор удаляется из системы вызовом int sem_unlink(const char *name);


#include <unistd.h>
// #include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include <fcntl.h>

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
	pid_t				pid;
	int					status;
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
// char					*ft_itoa(int n);
void					ft_putnbr_fd(long int n, int fd);
int						ft_strlen(char *str);

#endif
