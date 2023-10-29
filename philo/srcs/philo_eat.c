/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/29 20:37:43 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	take_fork(t_philo_data *data, \
				pthread_mutex_t *fork[], unsigned int *last_eat_time)
{
	pthread_mutex_lock(fork[0]);
	if (data->die_time <= get_ms_time() - *last_eat_time)
	{
		death_stop(data);
		pthread_mutex_unlock(fork[0]);
		return (false);
	}
	print_log(TKAE_FORK_MSG, NOMAL, data);
	if (data->num_philo == 1)
	{
		ft_usleep(data->die_time);
		death_stop(data);
		pthread_mutex_unlock(fork[0]);
		return (false);
	}
	pthread_mutex_lock(fork[1]);
	print_log(TKAE_FORK_MSG, NOMAL, data);
	return (true);
}

static int	unlock_tow_forks(pthread_mutex_t *fork[], int return_value)
{
	pthread_mutex_unlock(fork[1]);
	pthread_mutex_unlock(fork[0]);
	return (return_value);
}

bool	eat_philo(t_philo_data *data, \
		pthread_mutex_t *fork[], unsigned int *last_eat_time)
{
	if (take_fork(data, fork, last_eat_time) == false)
		return (false);
	if (print_log(EAT_MSG, NOMAL, data) == false)
		return (unlock_tow_forks(fork, false));
	*last_eat_time = get_ms_time();
	ft_usleep(data->eat_time);
	return (unlock_tow_forks(fork, true));
}
