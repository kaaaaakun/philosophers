/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:12:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:40:46 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	get_ms_time(void);
void	ft_usleep(useconds_t ms);
void	until_sleep(useconds_t ms)

long long int	get_ms_time(void)
{
	long long int	ms;
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(useconds_t ms)
{
	long long int	start_ms;
	long long int	now_ms;

	start_ms = get_ms_time();
	while (true)
	{
		now_ms = get_ms_time();
		if (ms <= now_ms - start_ms)
			break ;
	}
}

void	until_sleep(useconds_t ms)
{
	long long int	now_ms;

	while (true)
	{
		now_ms = get_ms_time();
		if (ms <= now_ms)
			break ;
	}
}
