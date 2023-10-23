/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/23 21:18:06 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# ifndef DEBUG
# define DEBUG 0
# endif

void	*routine_philo_life(void *philo_status);
int		is_other_philo_dead(int philo_id, t_mutex *mutex_struct);
int		set_fork(t_philo_status *philosopher, pthread_mutex_t *fork[]);
int		get_fork_and_eat_philo(t_philo_status *philosopher, pthread_mutex_t *fork[], long long int last_eat_time);
int		set_deth_flag(int philo_id, t_mutex *mutex_struct);
long long int	get_time_left_of_philo_died(int philo_id, long long int last_eat_time, t_philo_routine_data *routine_data);

int		set_fork(t_philo_status *philosopher, pthread_mutex_t *fork[])
{
	t_mutex					*mutex_struct;
    int						philo_id;

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

int	check_and_add_eat_status(t_philo_status *philosopher)
{
    int						philo_id;
	t_mutex					*mutex_struct;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;

	dprintf(2,"check_eat id %p/%d: count %d\n",philosopher,philosopher->philo_id, philosopher->eat_count);
	pthread_mutex_lock(&philosopher->philo_eat_count_mutex);
	if (philosopher->eat_count < 0)
	{
		pthread_mutex_unlock(&philosopher->philo_eat_count_mutex);
		return (-1);
	}
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->philo_eat_count_mutex);
	return (0);
	(void)philo_id;
	(void)mutex_struct;
}

int		get_fork_and_eat_philo(t_philo_status *philosopher, pthread_mutex_t *fork[], long long int last_eat_time)
{
	long long int			time_left;
    int						philo_id;
	t_mutex					*mutex_struct;

	dprintf(2,"get_fork id %p/%d : count %d\n",philosopher,philosopher->philo_id, philosopher->eat_count);
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	pthread_mutex_lock(fork[0]);
	if (is_other_philo_dead(philo_id, mutex_struct) == -1)
	{
		if (DEBUG == 1)
			m_printf("someone_dead", philo_id, 1, mutex_struct);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
	m_printf(FORK, philo_id, 1, mutex_struct);
	pthread_mutex_lock(fork[1]);
	m_printf(FORK, philo_id, 1, mutex_struct);
	m_printf(EAT, philo_id, 1, mutex_struct);
	
	time_left = get_time_left_of_philo_died(philo_id, last_eat_time, philosopher->routine_data);//死ぬまでの時間
write(2,"S\n",2);
	if (time_left < philosopher->routine_data->time_to_eat / 1000)//死ぬまでの時間＜食べる時間
	{
		usleep(time_left * 1000);
		set_deth_flag(philo_id, mutex_struct);//死亡判定
		pthread_mutex_unlock(fork[1]);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
write(2,"S\n",2);
	usleep(philosopher->routine_data->time_to_eat);
write(2,"S\n",2);
	if (check_and_add_eat_status(philosopher) == -1)//食事回数をカウントして追加
	{
		pthread_mutex_unlock(fork[1]);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
write(2,"S\n",2);
	pthread_mutex_unlock(fork[1]);
	pthread_mutex_unlock(fork[0]);
	dprintf(2,"get_fork afer unlock id %p/%d : count %d\n",philosopher,philosopher->philo_id, philosopher->eat_count);
	return (SUCCESS);
}

int	sleep_philo(t_philo_status *philosopher);
int	sleep_philo(t_philo_status *philosopher)
{
	t_mutex					*mutex_struct;
    int						philo_id;
	t_philo_routine_data	*routine_data;

	routine_data = philosopher->routine_data;
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	if (is_other_philo_dead(philo_id, mutex_struct) == -1)
	{
		if (DEBUG == 1)
			m_printf("someone_dead", philo_id, 1, mutex_struct);
		return (-1);
	}
	if (routine_data->time_to_die - routine_data->time_to_sleep <= 0)
	{
		set_deth_flag(philo_id, mutex_struct);
		return (-1);
	}
	m_printf(SLEEP, philo_id, 1, mutex_struct);
	usleep(routine_data->time_to_sleep);
	return (SUCCESS);
}

int	think_philo(t_philo_status *philosopher);
int	think_philo(t_philo_status *philosopher)
{
	t_mutex					*mutex_struct;
    int						philo_id;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
	if (is_other_philo_dead(philo_id, mutex_struct) == -1)
	{
		if (DEBUG == 1)
			m_printf("someone_dead", philo_id, 1, mutex_struct);
		return (-1);
	}
	m_printf(THINK, philo_id, 1, mutex_struct);
	return (SUCCESS);
}

int	set_deth_flag(int philo_id, t_mutex *mutex_struct)
{
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	mutex_struct->deth_flag = DEAD;
	m_printf(DIED, philo_id, 1, mutex_struct);
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	return (0);
}

void	*routine_philo_life(void *philo_status)
{
	t_philo_status	*philosopher;
	long long int	last_eat_time;
    pthread_mutex_t	*fork[2];

	philosopher = (t_philo_status *)philo_status;
	set_fork(philosopher, fork);
	last_eat_time = only_get_ms_time();
	while (1)
	{
		if (get_fork_and_eat_philo(philosopher, fork, last_eat_time) != SUCCESS)
			return (NULL);
		last_eat_time = only_get_ms_time();
		if (sleep_philo(philosopher) != SUCCESS)
			return (NULL);
		if (think_philo(philosopher) != SUCCESS)
			return (NULL);
	}
	return (NULL);
}

long long int	get_time_left_of_philo_died(int philo_id, long long int last_eat_time, t_philo_routine_data *routine_data)
{
	long long int now_time;
	long long int time_left;

	now_time = only_get_ms_time();
	if (now_time == -1)
		return (-1);
	time_left = routine_data->time_to_die / 1000 - (now_time - last_eat_time);
	if (DEBUG == 1)
		dprintf(2,"id : %d \n \
		now %lld : last %lld \n \
		n-l %lld : tl %lld \n \
		ttd %lld : tte%lld :tts%lld\n", \
		philo_id, now_time,last_eat_time, \
		now_time - last_eat_time, time_left, \
		routine_data->time_to_die / 1000, \
		routine_data->time_to_eat / 1000, routine_data->time_to_sleep / 1000);
	return (time_left);
	(void)routine_philo_life;
}

int	is_other_philo_dead(int	philo_id, t_mutex *mutex_struct)
{
	pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
	if (mutex_struct->deth_flag == DEAD)
	{
		pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	return (0);
	(void)philo_id;
}
