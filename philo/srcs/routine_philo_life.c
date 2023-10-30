/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/30 16:28:44 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine_philo_life(void *philo_data);
static void	set_fork(t_philo_data *data, pthread_mutex_t **fork);
static void	add_eatcount(t_philo_data *data);
static void	wait_until_start_time(t_philo_data *data);

bool	make_philo_thread(t_monitor *monitor, t_philo_config *config)
{
	pthread_t		*thread_array;
	t_philo_data	*philo_array;
	unsigned int	i;

	thread_array = monitor->thread_array;
	philo_array = monitor->philo_array;
	i = 0;
	while (i < config->num_philo)
	{
		if (pthread_create(&thread_array[i], NULL, \
				routine_philo_life, (void *)&philo_array[i]) != 0)
		{
			set_stop_process(monitor->shared_data);
			join_philo_thread(thread_array, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	*routine_philo_life(void *philo_data)
{
	t_philo_data	*data;
	unsigned int	last_eat_time;
	pthread_mutex_t	*fork[2];

	data = (t_philo_data *)philo_data;
	last_eat_time = data->start_time;
	set_fork(data, fork);
	wait_until_start_time(data);
	while (should_routine_stop(data->shared_data) == NO)
	{
		if (eat_philo(data, fork, &last_eat_time) == false)
			break ;
		add_eatcount(data);
		if (sleep_philo(data, &last_eat_time) == false)
			break ;
		if (think_philo(data, &last_eat_time) == false)
			break ;
	}
	return (NULL);
}

static void	set_fork(t_philo_data *data, pthread_mutex_t **fork)
{
	pthread_mutex_t	*fork_array;
	unsigned int	id;

	fork_array = data->shared_data->fork;
	id = data->id;
	if (id % 2 == 1)
	{
		fork[0] = &fork_array[(id + 1) % data->num_philo];
		fork[1] = &fork_array[id % data->num_philo];
	}
	else
	{
		fork[0] = &fork_array[id % data->num_philo];
		fork[1] = &fork_array[(id + 1) % data->num_philo];
	}
}

static void	wait_until_start_time(t_philo_data *data)
{
	unsigned int	add_time;

	add_time = 0;
	if (data->num_philo % 2 == 1)
	add_time += data->eat_time / (data->num_philo - 1) * data->id;
	if (data->id % 2 == 1)
		add_time += data->eat_time / 2;
	wait_until_time(data->start_time + add_time);
}

static void	add_eatcount(t_philo_data *data)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	data->eat_count = data->eat_count + 1;
	pthread_mutex_unlock(&data->eat_count_mutex);
}
