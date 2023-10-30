/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/30 16:30:51 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo_data *data, \
				pthread_mutex_t *fork[], unsigned int *last_eat_time);
static int	unlock_tow_forks(pthread_mutex_t *fork[], int return_value);

bool	eat_philo(t_philo_data *data, \
		pthread_mutex_t *fork[], unsigned int *last_eat_time)
{
	if (take_fork(data, fork, last_eat_time) == false)
		return (false);
	*last_eat_time = get_ms_time();
	if (print_log(EAT_MSG, NOMAL, data) == false)
		return (unlock_tow_forks(fork, false));
	if (data->die_time < data->eat_time)
	{
		ft_usleep(data->die_time);
		death_stop(data);
		return (unlock_tow_forks(fork, false));
	}
	ft_usleep(data->eat_time);
	return (unlock_tow_forks(fork, true));
}

static int	take_fork(t_philo_data *data, \
				pthread_mutex_t *fork[], unsigned int *last_eat_time)
{
	pthread_mutex_lock(fork[0]);
	if (data->die_time < get_ms_time() - *last_eat_time)
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
