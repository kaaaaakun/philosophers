/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_in_panopticon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:52:52 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/23 18:20:55 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	set_and_make_panopticon_thread(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data);
void	*monitoring_in_panopticon(void *monitor_data);

void	set_and_make_panopticon_thread(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data)
{
	t_panopticon	panopticon_monitor;
	pthread_t		panopticon;
	
	panopticon_monitor.philo_data_arry = philo_data_arry;
	panopticon_monitor.mutex_struct = mutex_data;
	panopticon_monitor.routine_data = routine_data;
	pthread_create(&panopticon, NULL, monitoring_in_panopticon, (void *)&panopticon_monitor);
	pthread_join(panopticon, NULL);
}
	
void	monitoring_philo_deth_flag(t_mutex *mutex_struct, t_philo_routine_data *routine_data, t_philo_status **philo_data_arry)
{
	int	i;
	int	now_eat_count;

	i = 0;
	now_eat_count = 0;
	while (1)
	{
		i = 0;
		while (i < routine_data->num_of_philo)
		{
			pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
			if (mutex_struct->deth_flag == -1)
				return ;
			pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);

			pthread_mutex_lock(&philo_data_arry[i]->philo_eat_count_mutex);
			if (philo_data_arry[i]->eat_count < now_eat_count)
				now_eat_count = philo_data_arry[i]->eat_count;
			else
				now_eat_count = philo_data_arry[i]->eat_count;
			pthread_mutex_unlock(&philo_data_arry[i]->philo_eat_count_mutex);
			i++;
		}
	
		if (routine_data->number_of_times_each_philosopher_must_eat <= now_eat_count && routine_data->number_of_times_each_philosopher_must_eat != NON_VALUE)
		{
			i = 0;
			while (i < routine_data->num_of_philo)
			{	
				pthread_mutex_lock(&philo_data_arry[i]->philo_eat_count_mutex);
				philo_data_arry[i]->eat_count = STOP;
				pthread_mutex_unlock(&philo_data_arry[i]->philo_eat_count_mutex);
				i++;
			}
			return ;
		}

	}
}

void	*monitoring_in_panopticon(void *monitor_data)
{
	t_panopticon			*panopticon_monitor;
	t_philo_status			*philo_data_arry;
	t_philo_routine_data	*routine_data;
	t_mutex					*mutex_struct;

	panopticon_monitor = (t_panopticon *)monitor_data;
	routine_data = panopticon_monitor->routine_data;
	philo_data_arry = panopticon_monitor->philo_data_arry;
	mutex_struct = panopticon_monitor->mutex_struct;
	monitoring_philo_deth_flag(mutex_struct, routine_data, &philo_data_arry);
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	return (NULL);
	(void)philo_data_arry;
}
