/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:55:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/24 20:44:08 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo_life(void *philo_status);
int		is_other_philo_dead(t_philo_status *philosopher);
//int		loop_routine(t_philo_status *philosopher, pthread_mutex_t *fork[]);
int		set_fork(t_philo_status *philosopher, pthread_mutex_t *fork[]);
int		get_fork_and_eat_philo(t_philo_status *philosopher, pthread_mutex_t *fork[], long long int *last_eat_time);
int		set_deth_flag(int philo_id, t_mutex *mutex_struct);
//int		is_during_eating_philo_died(int philo_id, long long int last_eat_time, t_philo_routine_data *routine_data);
long long int	get_time_left_of_philo_died(int philo_id, long long int last_eat_time, t_philo_routine_data *routine_data);

int	ft_usleep(useconds_t	microseconds);
int	ft_usleep(useconds_t	microseconds)
{
	long long int	start_ms;
	long long int	now_ms;

	start_ms = only_get_ms_time();
	while (1)
	{
		now_ms = only_get_ms_time();
		if (microseconds <= (now_ms - start_ms) * 1000)
			break ;
//		usleep(1);
	}
	return (0);
}

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

int		get_fork_and_eat_philo(t_philo_status *philosopher, pthread_mutex_t *fork[], long long int *last_eat_time)
{
    int						philo_id;
  //  int						num_of_philo;
	t_mutex					*mutex_struct;
	long long int			time_left;

	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
//	num_of_philo = philosopher->routine_data->num_of_philo;
	pthread_mutex_lock(fork[0]);
//	if (is_other_philo_dead(philosopher) == -1)
//	{
//		if (DEBUG == -10)
//			m_printf("someone_dead", philo_id, 1, mutex_struct);
//		pthread_mutex_unlock(fork[0]);
//		return (-1);
//	}
	if (philosopher->routine_data->time_to_die < only_get_ms_time() - *last_eat_time)
	{
		set_deth_flag(philo_id, mutex_struct);//死亡判定
//		pthread_mutex_unlock(fork[0]);
//		return (-1);
	}
	m_printf(FORK, philo_id, 1, mutex_struct);
//	if (num_of_philo == 1)
//	{
//		ft_usleep(philosopher->routine_data->time_to_die);
//		set_deth_flag(philo_id, mutex_struct);//死亡判定
//		pthread_mutex_unlock(fork[0]);
//		return (-1);
//	}
	pthread_mutex_lock(fork[1]);
	m_printf(FORK, philo_id, 1, mutex_struct);
	if (m_printf(EAT, philo_id, 1, mutex_struct) < 0)
	{
		pthread_mutex_unlock(fork[1]);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
	
	time_left = get_time_left_of_philo_died(philo_id, *last_eat_time, philosopher->routine_data);//死ぬまでの時間
	//dprintf(2,"%d : %lld : %lld \n", philo_id, time_left, last_eat_time);)
	if (time_left < philosopher->routine_data->time_to_eat / 1000)//死ぬまでの時間＜食べる時間
	{
		if (0 < time_left)
			ft_usleep(time_left * 1000);
		set_deth_flag(philo_id, mutex_struct);//死亡判定
		pthread_mutex_unlock(fork[1]);
		pthread_mutex_unlock(fork[0]);
		return (-1);
	}
	ft_usleep(philosopher->routine_data->time_to_eat);
	pthread_mutex_unlock(fork[0]);
	pthread_mutex_unlock(fork[1]);
	if (is_other_philo_dead(philosopher) == -1)
	{
		return (-1);
	}
	return (SUCCESS);
}

int	sleep_philo(t_philo_status *philosopher, long long int *last_eat_time);
int	sleep_philo(t_philo_status *philosopher, long long int *last_eat_time)
{
	t_mutex					*mutex_struct;
    int						philo_id;
	t_philo_routine_data	*routine_data;

	routine_data = philosopher->routine_data;
	mutex_struct = philosopher->mutex_struct;
	philo_id = philosopher->philo_id;
//	if (is_other_philo_dead(philosopher) == -1)
//	{
//		return (-1);
//	}
	if (routine_data->time_to_die - routine_data->time_to_sleep <= 0)
	{
		set_deth_flag(philo_id, mutex_struct);
		return (-1);
	}
	*last_eat_time = only_get_ms_time();
	m_printf(SLEEP, philo_id, 1, mutex_struct);
	ft_usleep(routine_data->time_to_sleep);
	return (SUCCESS);
}

int	think_philo(t_philo_status *philosopher);
int	think_philo(t_philo_status *philosopher)
{
	t_mutex					*mutex_struct;
    int						philo_id;

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

void	meet_up(t_philo_status *philosopher)
{
	static int	meet_up_flag;
	int	num_of_philo;
	pthread_mutex_t	*meet_mutex;

	num_of_philo = philosopher->routine_data->num_of_philo;
	meet_mutex = &philosopher->mutex_struct->deth_flag_mutex;

	while(1)
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
	m_printf("start!", philosopher->philo_id, DEBUG, philosopher->mutex_struct);
//	if (philosopher->philo_id % 2 == 1)
//		usleep(2000);
}

void	meet_up_end(t_philo_status *philosopher)
{
	static int	philo_count;

	while(1)
	{
		pthread_mutex_lock(&philosopher->mutex_struct->deth_flag_mutex);
		if (philosopher->philo_id == philo_count)
		{
			m_printf("see you", philosopher->philo_id, DEBUG, philosopher->mutex_struct);
			philo_count++;
		}
		if (philo_count == philosopher->routine_data->num_of_philo)
			break ;
		pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);		
	}
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
	number_of_times_each_philosopher_must_eat = philosopher->routine_data->number_of_times_each_philosopher_must_eat;
//	if (philosopher->philo_id % 2 == 0)
//		usleep((philosopher->routine_data->num_of_philo - philosopher->philo_id) * 100);
//	else if (philosopher->philo_id % 2 == 1)
//		usleep((philosopher->routine_data->num_of_philo - philosopher->philo_id) * 100 + philosopher->routine_data->time_to_eat / 2);
	meet_up(philosopher);
	last_eat_time = only_get_ms_time();
	while (1)
	{
		if (get_fork_and_eat_philo(philosopher, fork, &last_eat_time) != SUCCESS)
			break ;
		i++;
		if (i == number_of_times_each_philosopher_must_eat)
			break ;
		if (is_other_philo_dead(philosopher) == -1)
			break ;
		if (sleep_philo(philosopher, &last_eat_time) != SUCCESS)
			break ;
		if (think_philo(philosopher) != SUCCESS)
			break ;
	}
//	if (philosopher->philo_id == philosopher->routine_data->num_of_philo - 1)
//	{
//		ft_usleep(100);
//		set_deth_flag(-1, philosopher->mutex_struct);//	擬似死亡判定
//	}
//	m_printf("see you", philosopher->philo_id, DEBUG, philosopher->mutex_struct);
	meet_up_end(philosopher);
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
	if (DEBUG == -10)
		dprintf(2,"id : %d \n \
		now %lld : last_eat_time %lld \n \
		diff now last %lld : time_left %lld \n \
		ttd %lld : tte%lld :tts%lld\n", \
		philo_id, now_time,last_eat_time, \
		now_time - last_eat_time, time_left, \
		routine_data->time_to_die / 1000, \
		routine_data->time_to_eat / 1000, routine_data->time_to_sleep / 1000);
	return (time_left);
	(void)routine_philo_life;
}

int	is_other_philo_dead(t_philo_status *philosopher)
{
	//pthread_mutex_lock(&philosopher->mutex_struct->deth_flag_mutex);
	//if (philosopher->mutex_struct->deth_flag == DEAD)
	//{
	//	pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);
	//	return (-1);
	//}
	//pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);
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
