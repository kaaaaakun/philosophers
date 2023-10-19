/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:18 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/19 20:54:17 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>>

# define INIT 0x0
# define ARGS_ERROR 0x1

typedef struct s_philo{
    int						philo_id;
    t_mutex					mutex_struct;;
	t_philo_routine_data	routine_data;
} t_philo;

typedef struct s_philo_routein_data{
    int	num_of_philo;
    int	time_to_die;
    int	ime_to_eat;
    int	time_to_sleep;
    int	eat_count;
} t_philo_routine_data;

typedef struct s_mutex{
    int *fork;
    int pre_print;
    int print;
} t_mutex;

//main.c
int main(int argc, char *argv);

//check_args.c
t_philo_routine_data	*check_args_and_make_routine_data(int argc, char *argv);

//mutex_init.c
t_mutex	*init_all_mutex_data(philosophers_info *philo_info);

//哲学者のルーティーン
//パノプティコン

//utils
//-philo_atoi.h
int	philo_atoi(const char *str, int *flag);

#endif
