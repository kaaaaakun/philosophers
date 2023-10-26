/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:56:57 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:37:23 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_philo(t_philo_status *philosopher, long long int *last_eat_time)
{
	t_mutex					*mutex_struct;
	int						philo_id;
	t_philo_routine_data	*routine_data;

	routine_data = philosopher->routine_data;
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	if (is_other_philo_dead(philosopher) == -1)
	{
		return (-1);
	}
	if (routine_data->time_to_die < routine_data->time_to_sleep)
	{
		m_printf(SLEEP, philo_id, 1, mutex_struct);
		ft_usleep(routine_data->time_to_die);
		set_deth_flag(philo_id, mutex_struct);
		return (-1);
	}
	*last_eat_time = only_get_ms_time();
	m_printf(SLEEP, philo_id, 1, mutex_struct);
	ft_usleep(routine_data->time_to_sleep);
	return (SUCCESS);
}

int	think_philo(t_philo_status *philosopher)
{
	t_mutex	*mutex_struct;
	int		philo_id;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	if (is_other_philo_dead(philosopher) == -1)
	{
		if (DEBUG == -10)
			m_printf("someone_dead", philo_id, 1, mutex_struct);
		return (-1);
	}
	m_printf(THINK, philo_id, 1, mutex_struct);
	return (SUCCESS);
}
