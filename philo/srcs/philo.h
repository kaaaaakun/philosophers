/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:18 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/21 19:30:11 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define INIT 0x0
# define ARGS_ERROR 0x1
# define DEAD -1


typedef struct s_philo_routein_data{
    int	num_of_philo;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	number_of_times_each_philosopher_must_eat;
	int	oder_from_panopticon;
} t_philo_routine_data;

typedef struct s_mutex{
    pthread_mutex_t *fork;
    pthread_mutex_t eat_count_mutex;
	int				eat_count;
    pthread_mutex_t deth_flag_mutex;
	int				deth_flag;
    pthread_mutex_t print;
} t_mutex;

typedef struct s_philo_status{
    int						philo_id;
    t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data;
} t_philo_status;

typedef struct s_monitoring_philo{
	t_philo_status			*philo_data_arry;
	t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data;
}t_panopticon;

//main.c
int main(int argc, char *argv[]);
int	exec_philo_task(t_philo_routine_data *routine_data, int *flag);

//check_args.c
t_philo_routine_data	*check_args_and_make_routine_data(int argc, char *argv[]);

//init.c
void	make_philo_threads(pthread_t *philo_pthread_arry,t_philo_status *philo_data_arry, t_philo_routine_data *routine_data);
void	set_data_in_philo_arry(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data);
t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info);

//哲学者のルーティーン
void	*routine_philo_life(void *philo_status);

//パノプティコン
void	set_and_make_panopticon_thread(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data);

//utils

long long int	get_ms_time(void);
//-philo_atoi.h
int	philo_atoi(const char *str, int *flag);

//end_of_philo
void	all_mutex_destroy(t_philo_routine_data *routine_data, t_mutex *mutex_data);
void	join_philo_thread(t_philo_routine_data *routine_data, pthread_t *philo_pthread_arry);

//debug.c
void    d_printf(char *msg, int nbr, char *str);
void	d_write(char *str, t_mutex *mutex_struct);
#endif
