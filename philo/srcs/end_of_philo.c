/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:04 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/23 17:43:37 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_mutex_destroy(t_philo_routine_data *routine_data, t_mutex *mutex_data);
void	join_philo_thread(t_philo_routine_data *routine_data, pthread_t *philo_pthread_arry);

void	join_philo_thread(t_philo_routine_data *routine_data, pthread_t *philo_pthread_arry)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		pthread_join(philo_pthread_arry[i], NULL);
		i++;
	}
}

void	all_mutex_destroy(t_philo_routine_data *philo_info, t_mutex *mutex_data)
{
	int	i;

	i = 0;
	while (i < philo_info->num_of_philo)
	{
		pthread_mutex_destroy(&mutex_data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex_data->deth_flag_mutex);
	pthread_mutex_destroy(&mutex_data->print);
}
