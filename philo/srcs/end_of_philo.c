/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:04 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/24 20:27:20 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philo_thread(t_philo_routine_data *routine_data, \
			pthread_t *philo_pthread_arry)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		pthread_join(philo_pthread_arry[i], NULL);
		i++;
	}
}

void	destroy_mutex(int num_of_philo, t_philo_status *philo_data_arry, \
			t_mutex *mutex_data)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{	
		pthread_mutex_destroy(&philo_data_arry[i].eat_count_mutex);
		pthread_mutex_destroy(&mutex_data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex_data->deth_flag_mutex);
	pthread_mutex_destroy(&mutex_data->print);
}

void	join_and_destory_mutex(t_philo_routine_data *routine_data, \
		pthread_t *philo_pthread_arry, t_philo_status *philo_data_arry, \
		t_mutex *mutex_data)
{
	join_philo_thread(routine_data, philo_pthread_arry);
	destroy_mutex(routine_data->num_of_philo, philo_data_arry, mutex_data);
	free(philo_pthread_arry);
	free(philo_data_arry);
	free(mutex_data->fork);
	free(mutex_data);
}
