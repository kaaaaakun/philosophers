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

void	set_and_make_panopticon_thread(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data)
{
	t_panopticon	panopticon_monitor;
	pthread_t		panopticon;
	
	panopticon_monitor->philo_data_arry = philo_data_arry;
	panopticon_monitor->mutex_struct = mutex_data;
	panopticon_monitor->routine_data = routine_data;
	pthread_create(&panopticon, NULL, monitoring_in_panopticon, (void *)panopticon_monitor);
	pthread_join(panopticon, NULL);
}

void	monitoring_in_panopticon(void *panopticon_monitor)
{
	t_philo_status	*philo_data_arry;
	int				i;

	panopticon_monitor = (t_panopticon *)panopticon_monitor;
	philo_data_arry = panopticon_monitor->philo_data_arry;
	while (1)
	{
		i = 0;
		while (i < panopticon_monitor->)
		{
			if (philo_data_arry[i]->eat_count == DEAD)
				break ;
			i++;
		}
	}
	panopticon_monitor->routine_data->oder_from_panopticon = -1;
	pthread_mutex_lock(panopticon_monitor->mutex_data->print);
	printf("%dさんが死にました。", i);
	pthread_mutex_unlock(panopticon_monitor->mutex_data->print);
	return ;
}
