/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:41:15 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/20 14:15:59 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_philo_threads(pthread_t *philo_pthread_arry,t_philo_status *philo_data_arry, t_philo_routine_data *routine_data);
void	set_data_in_philo_arry(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data);
t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info);

t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info)
{
	t_mutex	*mutex_data;
	int		i;

	//make_mutex_data
	mutex_data->fork = malloc(sizeof(int), philo_info->num_of_philo);
	mutex_data->print = 0;
	mutex_data->pre_print = 0;

	//mutex_fork_init
	i = 0;
	while (i < philo_info->num_of_philo)
	{
		pthread_mutex_init(&mutex_data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex_data->pre_print, NULL);
	pthread_mutex_init(&mutex_data->print, NULL);
}

void	set_data_in_philo_arry(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		philo_data_arry[i]->philo_id = i;
		philo_data_arry[i]->eat_count = 0;
		philo_data_arry[i]->mutex_struct = mutex_data;
		philo_data_arry[i]->routine_data = routine_data;
		philo_data_arry[i]->oder_from_panopricon = INIT;
		i++;
	}
}

void	make_philo_threads(pthread_t *philo_pthread_arry,t_philo_status *philo_data_arry, t_philo_routine_data *routine_data)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		pthread_create(&philo_pthread_arry[i], NULL, routine_philo_life, (void *)&philo_data_arry[i]);
		i++;
	}
}

