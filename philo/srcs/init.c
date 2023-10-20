/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:41:15 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/20 14:15:59 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_philo_threads(pthread_t *philo_pthread_arry,t_philo_status *philo_data_arry, t_philo_routine_data *routine_data);
void	set_data_in_philo_arry(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data);
t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info);

t_mutex	*init_all_mutex_data(t_philo_routine_data *philo_info)
{
	t_mutex	*mutex_data;
	int		i;

	mutex_data = (t_mutex *) malloc (sizeof(t_mutex) * 1);
	if (mutex_data == NULL)
		return (NULL);
	//make_mutex_data_init
	mutex_data->fork = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * philo_info->num_of_philo);
	if (mutex_data->fork == NULL)
	{
		free (mutex_data);
		return (NULL);
	}
	mutex_data->eat_count = 0;
	mutex_data->deth_flag = 0;

	//mutex_init
	i = 0;
	while (i < philo_info->num_of_philo)
	{
		pthread_mutex_init(&mutex_data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex_data->eat_count_mutex, NULL);
	pthread_mutex_init(&mutex_data->deth_flag_mutex, NULL);
	pthread_mutex_init(&mutex_data->print, NULL);
	return (mutex_data);
}

void	set_data_in_philo_arry(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data, t_mutex *mutex_data)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		philo_data_arry[i].philo_id = i;
		philo_data_arry[i].mutex_struct = mutex_data;
		philo_data_arry[i].routine_data = routine_data;
		i++;
	}
}

void	make_philo_threads(pthread_t *philo_pthread_arry,t_philo_status *philo_data_arry, t_philo_routine_data *routine_data)
{
	int	i;

	i = 0;
	while (i < routine_data->num_of_philo)
	{
		pthread_create(&philo_pthread_arry[i], NULL, &routine_philo_life, (void *)&philo_data_arry[i]);
		i++;
	}
}

