/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:22 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop_process(t_shared_data *data)
{
	pthread_mutex_lock(&data->shared_lock);
	data->terminate = YES;
	pthread_mutex_unlock(&data->shared_lock);
}

void	make_philo_thread(t_monitor *monitor, t_philo_config *config)
{
	pthread_t		*thread_array;
	t_philo_data	*philo_array;
	int				i;

	thread_array = monitor->thread_array;
	philo_array = monitor->philo_array;
	i = 0;
	while (i < config->num_philo)
	{
		if (pthread_create(thread_array + i, NULL, \
				&routine_philo_life, (void *)philo_array + i) != 0)
		{
			set_stop_process(monitor->shared_data);
			join_philo_thread(thread_array, i);
			return (false);
		}
		i++;
	}
}

void	set_fork(t_philo_data *data, pthread_mutex_t *fork[])
{
	pthread_mutex_t	*fork_array;
	int				id;

	fork_array = data->shared_data->fork;
	id = data->id;
	if (id == data->num_philo - 1)
	{
		fork[0] = &fork_array[0];
		fork[1] = &fork_array[id];
	}
	else if (id % 2 == 0)
	{
		fork[0] = &fork_array[id];
		fork[1] = &fork_array[id + 1];
	}
	else
	{
		fork[0] = &fork_array[id - 1];
		fork[1] = &fork_array[id];
	}
}

bool	should_routine_stop(t_shared_data *data)
{
	bool	terminate_flag;

	pthread_mutex_lock(&data->shared_lock);
	terminate_flag = data->terminate;
	pthread_mutex_unlock(&data->shared_lock);
	return (terminate_flag);
}

void	routine_philo_life(void *philo_data)
{
	t_philo_data	*data;
	unsigned int	last_eat_time;
	pthread_mutex_t	fork[2];
	int				i;
	int				must_eat;

	i = 0;
	data = (t_philo_data *)philo_data;
	last_eat_time = data->start_time;
	set_fork(data, &fork);
	wait_until_time(data->start_time);
	while (should_routine_stop(data->shared_data) == NO)
	{
		if (eat_philo(data, &fork, &last_eat_time) == false)
			break ;
		if (sleep_philo(data, &last_eat_time) == false)
			break ;
		if (think_philo(data) == false)
			break ;
	}
	wait_other_thread(data);
}

void	wait_other_thread(t_philo_data *data)
{
	static int	philo_count;

	while (1)
	{
		pthread_mutex_lock(&data->shared_data->shared_lock);
		if (data->id == philo_count)
		{
			if (DEBUG == -10)
				print_log("see you", DEBUG, data);
			philo_count++;
		}
		if (philo_count == data->num_philo)
			break ;
		pthread_mutex_unlock(&data->shared_data->shared_lock);
	}
	pthread_mutex_unlock(&data->shared_data->shared_lock);
}
