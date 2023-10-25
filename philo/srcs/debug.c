/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:11:47 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:17:01 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	d_printf(char *msg, int nbr, char *str);
void	d_write(char *str, t_mutex *mutex_struct);

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	m_printf(char *msg, int nbr, int type, t_mutex *mutex_struct)
{
	long long int			ms;
	static long long int	start_time;
	static int				count;
	static int				deth_flag;

	ms = only_get_ms_time();
	if (ms == -1)
		return (-1);
	pthread_mutex_lock(&mutex_struct->print);
	if (deth_flag == 1 && type != DEBUG)
	{
		pthread_mutex_unlock(&mutex_struct->print);
		return (-2);
	}
	if (type == DEAD)
		deth_flag = 1;
	if (count == 0)
	{
		start_time = ms;
		count++;
	}
	printf("\x1b[38;5;%d29m%lld %d %s\x1b[0m\n", nbr, ms - start_time, nbr, msg);
	pthread_mutex_unlock(&mutex_struct->print);
	return (0);
}
