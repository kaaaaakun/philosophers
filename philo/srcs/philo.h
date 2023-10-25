/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:18 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:39:15 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# define INIT 0x0
# define ARGS_ERROR 0x1

# define SUCCESS 0
# define DEAD -1

# define FORK " has taken a fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DIED " died"

typedef struct s_philo_routein_data{
	long long int	num_of_philo;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	number_of_times_each_philosopher_must_eat;
	long long int	standard_time;
}	t_philo_routine_data;

typedef struct s_mutex{
	pthread_mutex_t	*fork;
	pthread_mutex_t	deth_flag_mutex;
	int				deth_flag;
	pthread_mutex_t	print;
}	t_mutex;

typedef struct s_philo_status{
	int						philo_id;
	pthread_mutex_t			eat_count_mutex;
	int						eat_count;
	t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data;
}	t_philo_status;

typedef struct s_monitoring_philo{
	t_philo_status			*philo_data_arry;
	t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data;
}	t_panopticon;

//main.c
int						main(int argc, char *argv[]);
int						exec_philo_task(t_philo_routine_data *routine_data, \
							int *flag);

//check_args.c
t_philo_routine_data	*check_args_and_make_routine_data(int argc, \
							char *argv[]);

//init.c
void					make_philo_threads(pthread_t *philo_pthread_arry, \
		t_philo_status *philo_data_arry, t_philo_routine_data *routine_data);
void					set_data_in_philo_arry(t_philo_status *philo_data_arry, \
					t_philo_routine_data *routine_data, t_mutex *mutex_data);
t_mutex					*init_all_mutex_data(t_philo_routine_data *philo_info);

//哲学者のルーティーン
void					*routine_philo_life(void *philo_status);

//パノプティコン
void					set_and_make_panopticon_thread(\
		t_philo_status *philo_data_arry, \
		t_philo_routine_data *routine_data, t_mutex *mutex_data);

//-philo_atoi.h
int						philo_atoi(const char *str, int *flag);

//end_of_philo
void					all_mutex_destroy(t_philo_routine_data *routine_data, \
							t_mutex *mutex_data);
void					join_and_destory_mutex(\
		t_philo_routine_data *routine_data, pthread_t *philo_pthread_arry, \
		t_philo_status *philo_data_arry, t_mutex *mutex_data);

//print_msg
int						m_printf(char *msg, int nbr, \
								int type, t_mutex *mutex_struct);

//utils
long long int			only_get_ms_time(void);
void					*ft_malloc(size_t size);

int						is_other_philo_dead(t_philo_status *philosopher);
int						set_deth_flag(int philo_id, t_mutex *mutex_struct);
long long int			get_time_left_of_philo_died(int philo_id, \
		long long int last_eat_time, t_philo_routine_data *routine_data);

void					meet_up(t_philo_status *philosopher);
int						sleep_philo(t_philo_status \
					*philosopher, long long int *last_eat_time);

int						think_philo(t_philo_status *philosopher);
int						set_fork(t_philo_status *philosopher, \
									pthread_mutex_t *fork[]);
int						get_fork(t_philo_status *philosopher, \
						t_philo_routine_data *routine_data, \
				pthread_mutex_t *fork[], long long int *last_eat_time);

int						get_fork_and_eat_philo(t_philo_status \
							*philosopher, \
						pthread_mutex_t *fork[], long long int *last_eat_time);
int						ft_usleep(useconds_t ms);
#endif
