/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:41:15 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/19 20:54:15 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*init_all_mutex_data(philosophers_info *philo_info)
{
	t_mutex	*mutex_data;
	int		i;

	//make_mutex_data
	data->fork = ft_calloc(sizeof(int), philo_info->num_of_philo);
	data->print = 0;
	data->pre_print = 0;

	//mutex_init
	i = 0;
	while (i < philo_info->num_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&pre_print, NULL);
}
