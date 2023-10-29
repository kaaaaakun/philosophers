/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:35:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:36:02 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_log(char *msg, int type, t_philo_data *data)
{
	bool	should_print;

	should_print = true;
	pthread_mutex_lock(&data->shared_data->shared_lock);
	if (data->shared_data->terminate == NO || type == DEBUG)
	{
		printf("\x1b[38;5;%d29m%u %d %s\x1b[0m\n", \
			data->id + 1, get_ms_time() - data->start_time, data->id, msg);
	}
	else
		should_print = false;
	pthread_mutex_unlock(&data->shared_data->shared_lock);
	return (should_print);
}
