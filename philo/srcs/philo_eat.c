/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 19:46:17 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(useconds_t ms)
{
	long long int	start_ms;
	long long int	now_ms;

	start_ms = only_get_ms_time();
	while (1)
	{
		now_ms = only_get_ms_time();
		if (ms <= now_ms - start_ms)
			break ;
	}
	return (0);
}

int	set_fork(t_philo_status *philosopher, pthread_mutex_t *fork[])
{
	t_mutex	*mutex_struct;
	int		philo_id;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	if (philo_id % 2 == 0)
	{
		if (philo_id == philosopher->routine_data->num_of_philo - 1)
		{
			fork[0] = &mutex_struct->fork[0];
			fork[1] = &mutex_struct->fork[philo_id];
		}
		else
		{
			fork[0] = &mutex_struct->fork[philo_id];
			fork[1] = &mutex_struct->fork[philo_id + 1];
		}
	}
	else if (philo_id % 2 == 1)
	{
		fork[0] = &mutex_struct->fork[philo_id - 1];
		fork[1] = &mutex_struct->fork[philo_id];
	}
	return (0);
}

int	get_fork(t_philo_status *philosopher, t_philo_routine_data *routine_data, \
				pthread_mutex_t *fork[], long long int *last_eat_time)
{
	int	philo_id;
	int	num_of_philo;

	num_of_philo = routine_data->num_of_philo;
	philo_id = philosopher->philo_id;
	pthread_mutex_lock(fork[0]);
	if (routine_data->time_to_die \
			< only_get_ms_time() - *last_eat_time)
		set_deth_flag(philo_id, philosopher->mutex_struct);
	if (m_printf(FORK, philo_id, 1, philosopher->mutex_struct) != 0)
		return (-1);
	if (num_of_philo == 1)
	{
		ft_usleep(routine_data->time_to_die);
		set_deth_flag(philo_id, philosopher->mutex_struct);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
	pthread_mutex_lock(fork[1]);
	if (m_printf(FORK, philo_id, 1, philosopher->mutex_struct) != 0)
		return (-1);
	return (0);
}

int	unlock_tow_forks(pthread_mutex_t *fork[], int return_value)
{
	pthread_mutex_unlock(fork[1]);
	pthread_mutex_unlock(fork[0]);
	return (return_value);
}

int	get_fork_and_eat_philo(t_philo_status *philosopher, \
		pthread_mutex_t *fork[], long long int *last_eat_time)
{
	int				philo_id;
	int				num_of_philo;
	t_mutex			*mutex_struct;
	long long int	time_left;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	num_of_philo = philosopher->routine_data->num_of_philo;
	if (get_fork(philosopher, philosopher->routine_data, \
				fork, last_eat_time) != SUCCESS)
		return (-1);
	if (m_printf(EAT, philo_id, 1, mutex_struct) < 0)
		return (unlock_tow_forks(fork, -1));
	time_left = get_time_left_of_philo_died(philo_id, \
				*last_eat_time, philosopher->routine_data);
	if (time_left < philosopher->routine_data->time_to_eat)
	{
		if (0 < time_left)
			ft_usleep(time_left);
		set_deth_flag(philo_id, mutex_struct);
		return (unlock_tow_forks(fork, -1));
	}
	ft_usleep(philosopher->routine_data->time_to_eat);
	return (unlock_tow_forks(fork, SUCCESS));
}
