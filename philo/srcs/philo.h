/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:18 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/20 15:31:09 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>>

# define INIT 0x0
# define ARGS_ERROR 0x1
# define DEAD -1


typedef struct s_philo_routein_data{
    int	num_of_philo;
    int	time_to_die;
    int	ime_to_eat;
    int	time_to_sleep;
    int	number_of_times_each_philosopher_must_eat;
	int	oder_from_panopticon;
} t_philo_routine_data;

typedef struct s_mutex{
    int *fork;
    int pre_print;
    int print;
} t_mutex;

typedef struct s_philo_status{
    int						philo_id;
	int						eat_count;
    t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data
} t_philo_status;

typedef struct s_monitoring_philo{
	t_philo_status			*philo_data_arry;
	t_mutex					*mutex_struct;
	t_philo_routine_data	*routine_data;
}t_panopticon;

//main.c
int main(int argc, char *argv);
int	exec_philo_task(t_philo_routine_data routine_data);

//check_args.c
t_philo_routine_data	*check_args_and_make_routine_data(int argc, char *argv);

//init.c
t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info);
void	set_data_in_philo_arry(t_philo_status philo_data_arry, t_philo_routine_data routine_data, t_mutex mutex_data)

//哲学者のルーティーン
//パノプティコン

//utils

long long int	get_ms_time(void);
//-philo_atoi.h
int	philo_atoi(const char *str, int *flag);

#endif
