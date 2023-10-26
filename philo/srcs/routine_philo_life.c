/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:22 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meet_up(t_philo_status *philosopher)
{
	static int		meet_up_flag;
	int				num_of_philo;
	pthread_mutex_t	*meet_mutex;

	num_of_philo = philosopher->routine_data->num_of_philo;
	meet_mutex = &philosopher->mutex_struct->deth_flag_mutex;
	while (1)
	{
		pthread_mutex_lock(meet_mutex);
		if (meet_up_flag == 1)
			break ;
		if (philosopher->philo_id == num_of_philo - 1)
			meet_up_flag = 1;
		pthread_mutex_unlock(meet_mutex);
		usleep(1);
	}
	pthread_mutex_unlock(meet_mutex);
	if (DEBUG == -10)
		m_printf("start", philosopher->philo_id, \
						DEBUG, philosopher->mutex_struct);
}

void	meet_up_end(t_philo_status *philosopher)
{
	static int	philo_count;

	while (1)
	{
		pthread_mutex_lock(&philosopher->mutex_struct->deth_flag_mutex);
		if (philosopher->philo_id == philo_count)
		{
			if (DEBUG == -10)
				m_printf("see you", philosopher->philo_id, \
						DEBUG, philosopher->mutex_struct);
			philo_count++;
		}
		if (philo_count == philosopher->routine_data->num_of_philo)
			break ;
		pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);
	}
	if (philosopher->mutex_struct->deth_flag != DEAD)
		philosopher->mutex_struct->deth_flag = DEAD;
	pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);
}

void	*routine_philo_life(void *philo_status)
{
	t_philo_status	*philosopher;
	long long int	last_eat_time;
	pthread_mutex_t	*fork[2];
	int				i;
	int				number_of_times_each_philosopher_must_eat;

	i = 0;
	philosopher = (t_philo_status *)philo_status;
	set_fork(philosopher, fork);
	number_of_times_each_philosopher_must_eat = \
		philosopher->routine_data->number_of_times_each_philosopher_must_eat;
	meet_up(philosopher);
	last_eat_time = only_get_ms_time();
	while (1)
	{
		if (get_fork_and_eat_philo(philosopher, fork, \
								&last_eat_time) != SUCCESS)
			break ;
		if (++i == number_of_times_each_philosopher_must_eat || \
				is_other_philo_dead(philosopher) == -1 || \
			sleep_philo(philosopher, &last_eat_time) != SUCCESS || \
			think_philo(philosopher) != SUCCESS)
			break ;
	}
	return (meet_up_end(philosopher), NULL);
}

long long int	get_time_left_of_philo_died(int philo_id, \
		long long int last_eat_time, t_philo_routine_data *routine_data)
{
	long long int	now_time;
	long long int	time_left;

	now_time = only_get_ms_time();
	if (now_time == -1)
		return (-1);
	time_left = routine_data->time_to_die - (now_time - last_eat_time);
	if (DEBUG == -10)
		dprintf(2, "id : %d \n \
		now %lld : last_eat_time %lld \n \
		diff now last %lld : time_left %lld \n \
		ttd %lld : tte%lld :tts%lld\n", \
		philo_id, now_time, last_eat_time, \
		now_time - last_eat_time, time_left, \
		routine_data->time_to_die, \
		routine_data->time_to_eat, routine_data->time_to_sleep);
	return (time_left);
	(void)routine_philo_life;
}
