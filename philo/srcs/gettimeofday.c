/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:12:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/21 19:49:43 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long long int	get_ms_time(void);
long long int	only_get_ms_time(void);

long long int	get_ms_time(void)
{
	static int				count = 0;
	long long int			ms;
	static long long int	start_time = 0;
    struct timeval			time;
    
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
    ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (count == 0)
	{
		start_time = ms;
		count++;
	}
	return (ms - start_time);
}

long long int	only_get_ms_time(void)
{
	long long int			ms;
    struct timeval			time;
    
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
    ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}
