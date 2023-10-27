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

bool	is_need_stop()
{
}

bool	print_log(char *msg, int nbr, int type, t_mutex *mutex_struct)
{
	unsigned int	ms;
	unsigned int	start_time;

	pthread_mutex_lock(&mutex_struct->print);
	ms = get_ms_time();
	if (ms == -1)
		return (false);
//	if (is_need_stop() == true && type != DEBUG)
	if (deth_flag == 1 && type != DEBUG)
	{
		pthread_mutex_unlock(&mutex_struct->print);
		return (false);
	}
	printf("\x1b[38;5;%d29m%lld %d %s\x1b[0m\n", nbr, ms - start_time, nbr, msg);
	pthread_mutex_unlock(&mutex_struct->print);
	return (true);
}
