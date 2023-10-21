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
	t_philo_status	*philosopher;
	t_mutex			*mutex_struct;
    int				philo_id;
	int	i = 0;

	philosopher = (t_philo_status *)philo_status;
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;

	while (i < 10)
	{
		printf("%d deth_flag1:%d\n", philo_id, philosopher->mutex_struct->deth_flag);
		if (is_philo_dead(mutex_struct) == -1)
			return (NULL);
		i++;
		usleep(500);
	}
	
	printf("%d deth_flag1:%d\n", philo_id, philosopher->mutex_struct->deth_flag);
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	mutex_struct->deth_flag = DEAD;
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);

	printf("%d deth_flag2:%d\n", philo_id, philosopher->mutex_struct->deth_flag);
	pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);

	return (NULL);
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
