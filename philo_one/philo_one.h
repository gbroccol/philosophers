/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:51:15 by gbroccol          #+#    #+#             */
/*   Updated: 2020/12/29 16:08:57 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h> // delete
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

// struct			timeval  {
//   time_t			tv_sec ;   //used for seconds
//   suseconds_t	tv_usec ;   //used for microseconds
// }

// memset -  fill a byte string with a byte value

// usleep - приостанавливает работу потока

// gettimeofday - определяет время						int gettimeofday(struct timeval *tv, struct timezone *tz);

// pthread_create - Новый поток создаётся				int pthread_create(*ptherad_t, NULL, void* (*start_routine)(void*), void *arg);
// pthread_detach - обозначаем поток отсоединившимся	int pthread_detach(pthread_t thread);
					// очистит тебе все..
					//  При удачном завершении pthread_detach() возвращает код 0, ненулевое значение сигнализирует об ошибке.
// pthread_join - ожидания завершения потока			int pthread_join(thread_t tid, void **status);

// pthread_mutex_init									int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);		
// pthread_mutex_destroy								int pthread_mutex_destroy(pthread_mutex_t *mutex);
// pthread_mutex_lock									int pthread_mutex_lock(pthread_mutex_t *mutex);
// pthread_mutex_unlock									int pthread_mutex_unlock(pthread_mutex_t *mutex);

typedef struct			s_com
{
	unsigned int		phil_nmb;
    unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		meal_nmb;
}						t_com;

typedef struct			s_phil
{
	long int			start;
	int					nmb;
	char				*name;
	int					right;
	int					left;
	pthread_t			thread;
}						t_phil;

typedef struct			s_table
{
    pthread_mutex_t		*mutex;		//???
}						t_table;

typedef struct			s_all
{
	t_com				*com;
	t_table				*table;
    t_phil				*phil;
	int					die;
	// pthread_t			thread;
}						t_all;

t_phil			*init_phil(int phil_nmb);
t_table			*init_table(unsigned int phil_nmb);
t_all			*init_all(t_com *com, t_phil *phil, t_table *table);

int				pars_args(t_com *com, char **argv);
void			error();

void			*phil_die(void *args);
long int		get_time();

/*
** libft
*/
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			ft_putnbr_fd(int n, int fd);

#endif
