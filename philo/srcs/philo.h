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
	int				terminate;
}	t_shared_data;

typedef struct s_philo_data{
	unsigned int	id;
	unsigned int	num_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	start_time;
	pthread_mutex_t	eat_count_mutex;
	unsigned int	eat_count;
	t_shared_data	*shared_data;
}	t_philo_data;

typedef struct s_monitoring_philo{
	t_philo_data	*philo_array;
	pthread_t		*thread_array;
	t_shared_data	*shared_data;
	t_philo_config	*config;
}	t_monitor;

//main
bool	make_philo_config(int argc, char *argv[], t_philo_config *config);
bool 	init_all_data(t_monitor *monitor, t_philo_config *config);
bool	make_philo_thread(t_monitor *monitor, t_philo_config *config);
bool	make_monitor_thread(t_monitor *monitor, t_philo_config *config);
void	end_of_meal(t_monitor *monitor);

//routine
bool	eat_philo(t_philo_data *data, \
		pthread_mutex_t *fork[], unsigned int *last_eat_time);
bool	sleep_philo(t_philo_data *data, unsigned int *last_eat_time);
bool	think_philo(t_philo_data *data, unsigned int *last_eat_time);

//use_mutex
bool	print_log(char *msg, int type, t_philo_data *data);
void	set_stop_process(t_shared_data *data);
int		should_routine_stop(t_shared_data *data);
void	death_stop(t_philo_data *data);

//end_of_philo
void	join_philo_thread(pthread_t *philo_array, unsigned int num_philo);
void	destroy_all_mutex(t_monitor *monitor, int num_i , int num_j);
void	*free_all(t_monitor *monitor);

//utils
int	philo_atoi(const char *str, int *flag);
unsigned int	get_ms_time(void);
void	wait_until_time(unsigned int time);
void	ft_usleep(unsigned int time);
void	*ft_malloc(size_t size);
#endif
