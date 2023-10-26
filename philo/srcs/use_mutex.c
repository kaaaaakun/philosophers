/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:35:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:36:02 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_deth_flag(int philo_id, t_mutex *mutex_struct)
{
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	if (mutex_struct->deth_flag != DEAD)
		mutex_struct->deth_flag = DEAD;
	else
	{
		pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
		return (0);
	}
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	m_printf(DIED, philo_id, DEAD, mutex_struct);
	return (0);
}

int	is_other_philo_dead(t_philo_status *philosopher)
{
	pthread_mutex_lock(&philosopher->eat_count_mutex);
	if (philosopher->eat_count == DEAD)
	{
		pthread_mutex_unlock(&philosopher->eat_count_mutex);
		return (-1);
	}
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
	return (0);
}

int	m_printf(char *msg, int nbr, int type, t_mutex *mutex_struct)
{
	long long int			ms;
	static long long int	start_time;
	static int				count;
	static int				deth_flag;

	ms = only_get_ms_time();
	if (ms == -1)
		return (-1);
	pthread_mutex_lock(&mutex_struct->print);
	if (deth_flag == 1 && type != DEBUG)
	{
		pthread_mutex_unlock(&mutex_struct->print);
		return (-2);
	}
	if (type == DEAD)
		deth_flag = 1;
	if (count == 0)
	{
		start_time = ms;
		count++;
	}
	printf("\x1b[38;5;%d29m%lld %d %s\x1b[0m\n", nbr, ms - start_time, nbr, msg);
	pthread_mutex_unlock(&mutex_struct->print);
	return (0);
}
