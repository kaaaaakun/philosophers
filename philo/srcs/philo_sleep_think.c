/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   okazaki2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:56:57 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 17:37:23 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleep_philo(t_philo_data *data, unsigned int *last_eat_time)
{
	unsigned int	time_left;

	*last_eat_time = get_ms_time();
	if (print_log(SLEEP_MSG, NOMAL, data) == false)
		return (false);
	time_left = *last_eat_time + data->die_time;
	if (time_left < get_ms_time() + data->sleep_time)
	{
		wait_until_time(time_left);
		death_stop(data);
		return (false);
	}
	ft_usleep(data->sleep_time);
	return (true);
}

bool	think_philo(t_philo_data *data)
{
	if (print_log(THINK_MSG, NOMAL, data) == false)
		return (false);
	return (true);
}
