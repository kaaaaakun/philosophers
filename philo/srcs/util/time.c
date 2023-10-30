/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:12:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/30 16:33:58 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>

unsigned int	get_ms_time(void);
void			ft_usleep(unsigned int ms);
void			wait_until_time(unsigned int ms_time);

unsigned int	get_ms_time(void)
{
	unsigned int	ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(unsigned int ms)
{
	unsigned int	start_ms;
	unsigned int	now_ms;

	start_ms = get_ms_time();
	while (1)
	{
		now_ms = get_ms_time();
		if (ms <= now_ms - start_ms)
			break ;
		usleep(10);
	}
}

void	wait_until_time(unsigned int ms_time)
{
	while (1)
	{
		if (ms_time <= get_ms_time())
			break ;
		usleep(10);
	}
}
