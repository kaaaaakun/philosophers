/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:04 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/24 20:27:20 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	free_all(t_monitor *monitor)
{
	free(monitor->shared_data->fork);
	free(monitor->shared_data);
	free(monitor->config);
	free(monitor->philo_array);
	free(monitor);
	return (false);
}

void	destroy_all_mutex(t_monitor *monitor, t_philo_config *config, int i , int j)
{
	t_shared_data	*mutex_data;
	t_philo_data	*philo_data_array;

	philo_data_array = monitor->philo_array;
	mutex_data = monitor->shared_data;
	while (j--)
		pthread_mutex_destroy(&mutex_data->fork[j]);
	while (i--)
		pthread_mutex_destroy(&philo_data_array[i].eat_count_mutex);
	pthread_mutex_destroy(&mutex_data->shared_lock);
}

void	join_philo_thread(pthread_t *philo_array, unsigned int num_philo)
{
	unsigned int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_join(philo_array[i], NULL);
		i++;
	}
}

/// @brief 
/// @param num_of_philo 
/// @param philo_data_arry 
/// @param mutex_data 
void	destroy_mutex(int num_of_philo, t_philo_status *philo_data_arry, \
			t_mutex *mutex_data)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{	
		pthread_mutex_destroy(&philo_data_arry[i].eat_count_mutex);
		pthread_mutex_destroy(&mutex_data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex_data->deth_flag_mutex);
	pthread_mutex_destroy(&mutex_data->print);
}

void	join_and_destory_mutex(t_philo_routine_data *routine_data, \
		pthread_t *philo_pthread_arry, t_philo_status *philo_data_arry, \
		t_mutex *mutex_data)
{
	join_philo_thread(routine_data, philo_pthread_arry);
	destroy_mutex(routine_data->num_of_philo, philo_data_arry, mutex_data);
	free(philo_pthread_arry);
	free(philo_data_arry);
	free(mutex_data->fork);
	free(mutex_data);
}
