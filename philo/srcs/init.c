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

int	init_all_data(t_monitor *monitor, t_philo_config *config)
{
	if (build_dataset(monitor, config) == false)
		return (false);
	set_data_in_philo_array(monitor, config);
	if (init_all_mutex_data(monitor, config) == false)
		return (free_all(monitor));

//ここから
	make_philo_threads(philo_pthread_arry, philo_data_arry, config);
	set_and_make_panopticon_thread(philo_data_arry, config, mutex_data);
	join_and_destory_mutex(config, philo_pthread_arry, \
			philo_data_arry, mutex_data);
	return (0);
}
//malloc_data
//init_mutex
//set_data_in_philo

bool	free_all(t_monitor *monitor)
{
	free(monitor->shared_data->fork);
	free(monitor->shared_data);
	free(monitor->config);
	free(monitor->philo_array);
	free(monitor);
	return (false);
}

static bool	build_dataset(t_monitor *monitor, t_philo_config *config)
{
	t_philo_data	*philo_data_array;
	t_shared_data	*mutex_data;

	monitor = malloc(sizeof(t_monitor));
	philo_data_array = malloc(sizeof(t_philo_data) * config->num_philo);
	mutex_data = malloc(sizeof(t_shared_data));
	if (mutex_data != NULL)
		mutex_data->fork = malloc (sizeof(pthread_mutex_t) * config->num_philo);
	if (monitor == NULL || philo_data_array == NULL || \
			mutex_data == NULL || mutex_data->fork == NULL)
	{
		if (mutex_data != NULL)
			free(mutex_data->fork);
		free(mutex_data);
		free(monitor);
		free(config);
		free(philo_data_array);
		return (false);
	}
	monitor->config = config;
	monitor->philo_array = philo_data_array;
	monitor->shared_data = mutex_data;
	return (true);
}

void	set_data_in_philo_array(t_monitor *monitor, t_philo_config *config)
{
	t_philo_data	*philo_data_arry;
	int				i;

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

bool	init_all_mutex_data(t_monitor *monitor, t_philo_config *config)
{
	t_shared_data	*mutex_data;
	t_philo_data	*philo_data_array;
	int				i;
	int				j;

	philo_data_array = monitor->philo_array;
	mutex_data = monitor->shared_data;
	mutex_data->terminate = ALIVE;
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
	destroy_all_mutex(monitor, config, i, j);
	return (false);
}

void	make_philo_threads(pthread_t *philo_pthread_arry, \
			t_philo_status *philo_data_arry, t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		pthread_create(&philo_pthread_arry[i], NULL, \
				&routine_philo_life, (void *)&philo_data_arry[i]);
		i++;
	}
}
