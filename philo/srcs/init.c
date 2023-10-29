/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:41:15 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/27 20:54:11 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_monitor	*build_dataset(t_monitor *monitor, t_philo_config *config);
static void	set_data_in_philo_array(t_monitor *monitor, t_philo_config *config);
static bool	init_all_mutex_data(t_monitor *monitor, t_philo_config *config);

bool	init_all_data(t_monitor *monitor, t_philo_config *config)
{
	if (build_dataset(monitor, config) == false)
		return (false);
	set_data_in_philo_array(monitor, config);
	if (init_all_mutex_data(monitor, config) == false)
		return (free_all(monitor));
	return (monitor);
}

t_monitor	*build_dataset(t_monitor *monitor, t_philo_config *config)
{
	monitor->philo_array = ft_malloc(sizeof(t_philo_data) * config->num_philo);
	monitor->thread_array = ft_malloc(sizeof(pthread_t) * config->num_philo);
	monitor->shared_data = ft_malloc(sizeof(t_shared_data));
	if (monitor->shared_data != NULL)
		monitor->shared_data->fork \
		= ft_malloc(sizeof(pthread_mutex_t) * config->num_philo);
	if (monitor->philo_array == NULL || monitor->thread_array == NULL || \
		monitor->shared_data == NULL || monitor->shared_data->fork == NULL)
		return (free_all(monitor));
	monitor->config = config;
	return (monitor);
}

static void	set_data_in_philo_array(t_monitor *monitor, t_philo_config *config)
{
	t_philo_data	*philo_data_arry;
	unsigned int	i;

	i = 0;
	philo_data_arry = monitor->philo_array;
	while (i < config->num_philo)
	{
		philo_data_arry[i].id = i;
		philo_data_arry[i].num_philo = config->num_philo;
		philo_data_arry[i].die_time = config->die_time;
		philo_data_arry[i].eat_time = config->eat_time;
		philo_data_arry[i].sleep_time = config->sleep_time;
		philo_data_arry[i].start_time = config->start_time;
		philo_data_arry[i].eat_count = 0;
		philo_data_arry[i].shared_data = monitor->shared_data;
		i++;
	}
}

static bool	init_all_mutex_data(t_monitor *monitor, t_philo_config *config)
{
	t_shared_data	*mutex_data;
	t_philo_data	*philo_data_array;
	unsigned int	i;
	unsigned int	j;

	mutex_data = monitor->shared_data;
	philo_data_array = monitor->philo_array;
	mutex_data->terminate = NO;
	i = 0;
	j = 0;
	if (pthread_mutex_init(&mutex_data->shared_lock, NULL) != 0)
		return (false);
	while (i < config->num_philo)
	{
		if (pthread_mutex_init(&mutex_data->fork[j], NULL) != 0)
			break ;
		j++;
		if (pthread_mutex_init(&philo_data_array[i].eat_count_mutex, NULL) != 0)
			break ;
		i++;
	}
	if (i == config->num_philo)
		return (true);
	destroy_all_mutex(monitor, i, j);
	return (false);
}
