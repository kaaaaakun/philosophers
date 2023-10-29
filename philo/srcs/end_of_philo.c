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

void	*free_all(t_monitor *monitor)
{
	if (monitor->shared_data != NULL)
		free(monitor->shared_data->fork);
	free(monitor->shared_data);
	free(monitor->philo_array);
	free(monitor->thread_array);
	return (NULL);
}

void	destroy_all_mutex(t_monitor *monitor, int num_i , int num_j)
{
	t_shared_data	*mutex_data;
	t_philo_data	*philo_data_array;

	philo_data_array = monitor->philo_array;
	mutex_data = monitor->shared_data;
	while (num_j--)
		pthread_mutex_destroy(&mutex_data->fork[num_j]);
	while (num_i--)
		pthread_mutex_destroy(&philo_data_array[num_i].eat_count_mutex);
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

void	end_of_meal(t_monitor *monitor)
{
	join_philo_thread(monitor->thread_array, monitor->config->num_philo);
	destroy_all_mutex(monitor, \
				monitor->config->num_philo, monitor->config->num_philo);
	free_all(monitor);
}