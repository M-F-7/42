/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:23:24 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 14:59:48 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERROR 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum s_thread
{
	CREATE,
	DETACH,
	JOIN
}					t_thread;

typedef enum s_mutex
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}					t_mutex;

typedef struct s_philo
{
	int				id;
	long			nb_meals;
	int				full;
	long			time_since_eat;
	long			last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				nb_philo;
	long			ttd;
	long			tte;
	long			tts;
	long			max_meals;
	int				end;
	pthread_mutex_t	end_mutex;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork[200];
	t_philo			philo[200];
}					t_info;

// MONITORING

void				*monitor_routine(void *arg);

// SAFE PRINTF

void				safe_printf(t_philo *philo, const char *msg);
long				get_time_ms(void);

// ERRORS
int					check_args(int ac, char **av);

// UTILS
char				*valid_input(char *s);
long				ft_atol(char *s);
int					ttk(t_philo *philo);

// ROUTINE
void				*philo_routine(void *arg);

// INIT_ARGS
int					init_args(t_info *info, char **av);
void				init_info(t_info *info);
void				init_philo(t_info *info);
void				init_forks(t_info *info, t_philo *philo, int i);

// handle_MUTEX
void				safe_handle_mutex(pthread_mutex_t *mtx, t_mutex code);

// HANDE_THREAD
void				safe_handle_thread(pthread_t *thread, void *(*foo)(void *),
						void *data, t_thread code);
#endif