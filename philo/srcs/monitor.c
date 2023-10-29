/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_in_panopticon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:52:52 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:43:31 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <stdbool.h>

bool		make_monitor_thread(t_monitor *monitor, t_philo_config *config);
void	*philo_monitor(void *monitor_tmp);

bool	make_monitor_thread(t_monitor *monitor, t_philo_config *config)
{
	pthread_t	monitor_thread;

	if (config->has_option == true)
		return (true);
	if (pthread_create(&monitor_thread, NULL, philo_monitor, (void *)monitor) != 0)
	{
		set_stop_process(monitor->shared_data);
		destroy_all_mutex(monitor, config->num_philo, config->num_philo);
		join_philo_thread(monitor->thread_array, config->num_philo);
		free_all(monitor);
		return (false);
	}
	return (true);
}

void	*philo_monitor(void *monitor_tmp)
{
	t_philo_data	*philo_array;
	t_monitor		*monitor;
	int				least_eat_count;
	int				num_philo;
	int 			i;

	monitor = (t_monitor *)monitor_tmp;
	philo_array = monitor->philo_array;
	num_philo = monitor->config->num_philo;
	while (should_routine_stop(monitor->shared_data) == NO)
	{
		i = 0;
		while (i < num_philo)
		{
			pthread_mutex_lock(&philo_array[i].eat_count_mutex);
			if (i == 0 || philo_array[i].eat_count < least_eat_count)
				least_eat_count = philo_array[i].eat_count;
			pthread_mutex_unlock(&philo_array[i].eat_count_mutex);
			i++;
		}
		if (least_eat_count == num_philo)
		set_stop_process(monitor->shared_data);
	}
	return (NULL);
}