/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/29 20:42:55 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo_life(void *philo_data);
void	wait_other_thread(t_philo_data *data);

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

void	set_stop_process(t_shared_data *data)
{
	pthread_mutex_lock(&data->shared_lock);
	data->terminate = YES;
	pthread_mutex_unlock(&data->shared_lock);
}

void	set_fork(t_philo_data *data, pthread_mutex_t **fork)
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

int	should_routine_stop(t_shared_data *data)
{
	int	terminate_flag;

	pthread_mutex_lock(&data->shared_lock);
	terminate_flag = data->terminate;
	pthread_mutex_unlock(&data->shared_lock);
	return (terminate_flag);
}

static void	add_eatcount(t_philo_data *data)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	data->eat_count = data->eat_count + 1;
	pthread_mutex_unlock(&data->eat_count_mutex);
}

void	*routine_philo_life(void *philo_data)
{
	t_philo_data	*data;
	unsigned int	last_eat_time;
	pthread_mutex_t	*fork[2];

	data = (t_philo_data *)philo_data;
//	last_eat_time = data->start_time;
	set_fork(data, fork);
	if (data->id % 2 == 0)
		wait_until_time(data->start_time);
	else
		wait_until_time(data->start_time + data->eat_time / 2);
	if (data->num_philo % 2 == 1)
		ft_usleep(data->eat_time / data->num_philo * data->id);
	while (should_routine_stop(data->shared_data) == NO)
	{
		last_eat_time = get_ms_time();
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
