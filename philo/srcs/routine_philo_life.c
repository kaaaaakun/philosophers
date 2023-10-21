/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/21 20:14:21 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo_life(void *philo_status);
int	is_philo_dead(t_mutex *mutex_struct);

void	*routine_philo_life(void *philo_status)
{
	t_philo_status			*philosopher;
	t_mutex					*mutex_struct;
    int						philo_id;
	t_philo_routine_data	*routine_data;
    pthread_mutex_t			fork[2];
	int	i = 0;

	philosopher = (t_philo_status *)philo_status;
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	routine_data = philosopher->routine_data;

	if (philo_id % 2 == 0)
	{
		fork[0] = mutex_struct->fork[philo_id];
		if (philo_id == philosopher->routine_data->num_of_philo)
			fork[1] = mutex_struct->fork[0];
		else
			fork[1] = mutex_struct->fork[philo_id + 1];
		m_printf("ph_id %% 2", philo_id, 1, mutex_struct);
	}
	else if (philo_id % 2 == 1)
	{
		fork[0] = mutex_struct->fork[philo_id - 1];
		fork[1] = mutex_struct->fork[philo_id];
	}

	while (i < 10)
	{
		if (is_philo_dead(mutex_struct) == -1)
		{
			m_printf("someone_dead", philo_id, 1, mutex_struct);
			return (NULL);
		}
		//eat
		pthread_mutex_lock(&fork[0]);
		pthread_mutex_lock(&fork[1]);
		m_printf("eat now", philo_id, 1, mutex_struct);
		usleep(routine_data->time_to_eat);
		pthread_mutex_unlock(&fork[1]);
		pthread_mutex_unlock(&fork[0]);
		//sleep
		m_printf("sleep now", philo_id, 1, mutex_struct);
		usleep(routine_data->time_to_sleep);
		//think
		m_printf("think now", philo_id, 1, mutex_struct);
	}
	
	m_printf("deth_flag", philo_id, 1, mutex_struct);
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	mutex_struct->deth_flag = DEAD;
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);

	return (NULL);
	(void)i;
	(void)philosopher;
}

int	is_philo_dead(t_mutex *mutex_struct)
{
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	if (mutex_struct->deth_flag == DEAD)
	{
		pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	return (0);
}
