/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_in_panopticon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:52:52 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/20 15:10:05 by tokazaki         ###   ########.fr       */
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

void	*monitoring_in_panopticon(void *monitor_data)
{
	t_panopticon			*panopticon_monitor;
	t_philo_status			*philo_data_arry;
	t_philo_routine_data	*routine_data;
	t_mutex					*mutex_struct;
	int						i;

	panopticon_monitor = (t_panopticon *)monitor_data;
	routine_data = panopticon_monitor->routine_data;
	philo_data_arry = panopticon_monitor->philo_data_arry;
	mutex_struct = panopticon_monitor->mutex_struct;
	d_write("cc", mutex_struct);
	while (1)
	{
		i = 0;
		while (i < routine_data->num_of_philo)
		{
			d_write("e", mutex_struct);
			pthread_mutex_lock(&mutex_struct->deth_flag_mutex);
			if (mutex_struct->deth_flag == -1)
			{
				d_write("[break]", mutex_struct);
				break ;
			}
			pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
			i++;
		}
		if (mutex_struct->deth_flag == -1)
		{
			d_write("[break]", mutex_struct);
			break ;
		}
	d_write("c", mutex_struct);
	}
	d_write("f", mutex_struct);
	pthread_mutex_unlock(&mutex_struct->deth_flag_mutex);
	//
	pthread_mutex_lock(&panopticon_monitor->mutex_struct->print);
	d_printf("[OOさんが死にました]",0,"");
	pthread_mutex_unlock(&panopticon_monitor->mutex_struct->print);
	return (NULL);
	(void)philo_data_arry;
}
