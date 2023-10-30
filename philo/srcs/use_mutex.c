/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:35:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/30 16:30:13 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_log(char *msg, int type, t_philo_data *data)
{
	bool	should_print;

	should_print = true;
	pthread_mutex_lock(&data->shared_data->shared_lock);
	if (data->shared_data->terminate == NO)
	{
		printf("\x1b[38;5;%d29m%u %d %s\x1b[0m\n", \
				data->id + 2, get_ms_time() - data->start_time, \
				data->id + 1, msg);
	}
	else
		should_print = false;
	if (type != 0)
	{
		printf("\x1b[38;5;%d29m%u %d %s\x1b[0m\n", \
				data->id + 2, get_ms_time() - data->start_time, \
				data->id + 1, msg);
	}
	pthread_mutex_unlock(&data->shared_data->shared_lock);
	return (should_print);
}

void	set_stop_process(t_shared_data *data)
{
	pthread_mutex_lock(&data->shared_lock);
	data->terminate = YES;
	pthread_mutex_unlock(&data->shared_lock);
}

int	should_routine_stop(t_shared_data *data)
{
	int	terminate_flag;

	pthread_mutex_lock(&data->shared_lock);
	terminate_flag = data->terminate;
	pthread_mutex_unlock(&data->shared_lock);
	return (terminate_flag);
}

void	death_stop(t_philo_data *data)
{
	unsigned int	ms_time;

	pthread_mutex_lock(&data->shared_data->shared_lock);
	if (data->shared_data->terminate == NO)
	{
		data->shared_data->terminate = YES;
		ms_time = get_ms_time() - data->start_time;
		printf("\x1b[38;5;%d29m%u %d %s\x1b[0m\n", \
		data->id + 2, ms_time, data->id + 1, DIE_MSG);
	}
	pthread_mutex_unlock(&data->shared_data->shared_lock);
}
