/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:18 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/27 14:17:43 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# define INIT 0
# define INVALID_ARGUMENTS 1

# define NOMAL 0

# define NO 0
# define YES 1

# define SUCCESS 0
# define DEAD -1

# define TKAE_FORK_MSG " has taken a fork"
# define EAT_MSG " is eating"
# define SLEEP_MSG " is sleeping"
# define THINK_MSG " is thinking"
# define DIE_MSG " died"

typedef struct s_philo_config{
	unsigned int	num_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	must_eat_count;
	bool			has_option;
	unsigned int	start_time;
}	t_philo_config;

typedef struct s_shared_data{
	pthread_mutex_t	*fork;
	pthread_mutex_t	shared_lock;
	bool			terminate;
}	t_shared_data;

typedef struct s_philo_data{
	int				id;
	unsigned int	num_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	start_time;
	pthread_mutex_t	eat_count_mutex;
	int				eat_count;
	t_shared_data	*shared_data;
}	t_philo_data;

typedef struct s_monitoring_philo{
	t_philo_data	*philo_array;
	pthread_t		*thread_array;
	t_shared_data	*shared_data;
	t_philo_config	*config;
}	t_monitor;

bool	print_log(char *msg, int type, t_philo_data *data);
bool	eat_philo(t_philo_data *data, \
		pthread_mutex_t *fork[], unsigned int *last_eat_time);
//main.c
int						main(int argc, char *argv[]);
int						exec_philo_task(t_philo_routine_data *routine_data, \
							int *flag);

//check_args.c
t_philo_routine_data	*check_args_and_make_routine_data(int argc, \
							char *argv[]);

//init.c
void					make_philo_threads(pthread_t *philo_pthread_array, \
		t_philo_status *philo_data_array, t_philo_routine_data *routine_data);
void					set_data_in_philo_array(t_philo_status *philo_data_array, \
					t_philo_routine_data *routine_data, t_mutex *mutex_data);
t_mutex					*init_all_mutex_data(t_philo_routine_data *philo_info);

//哲学者のルーティーン
void					*routine_philo_life(void *philo_status);

//パノプティコン
void					set_and_make_panopticon_thread(\
		t_philo_status *philo_data_array, \
		t_philo_routine_data *routine_data, t_mutex *mutex_data);

//philo_atoi.h
int						philo_atoi(const char *str, int *flag);

//end_of_philo
void					all_mutex_destroy(t_philo_routine_data *routine_data, \
							t_mutex *mutex_data);
void					join_and_destory_mutex(\
		t_philo_routine_data *routine_data, pthread_t *philo_pthread_array, \
		t_philo_status *philo_data_array, t_mutex *mutex_data);

//print_msg

//utils
long long int			get_ms_time(void);
void					*ft_malloc(size_t size);

int						is_other_philo_dead(t_philo_status *philosopher);
int						set_death_flag(int philo_id, t_mutex *mutex_struct);
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
