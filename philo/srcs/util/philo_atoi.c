/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:32:37 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:11:14 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static long long int	plus_atoi(const char *str, int *flag)
{
	long long int	result;
	long long int	l_divis;
	char			l_remain;
	int				i;

	i = 0;
	result = 0;
	l_divis = LONG_MAX / 10;
	l_remain = LONG_MAX % 10 + '0';
	if (!ft_isdigit(str[i]))
	{
		return (0);
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (INT_MAX < result)
			*flag = INVALID_ARGUMENTS;
		i++;
	}
	if (str[i] != '\0')
		*flag = INVALID_ARGUMENTS;
	return (result);
}

static long long int	minus_atoi(const char *str, int *flag)
{
	long long int	result;
	long long int	l_divis;
	char			l_remain;
	int				i;

	i = 0;
	result = 0;
	l_divis = LONG_MIN / 10;
	l_remain = (LONG_MIN % 10 * -1) + '0';
	while (ft_isdigit(str[i]))
	{
		result = result * 10 - (str[i] - '0');
		if (result < INT_MIN)
			*flag = INVALID_ARGUMENTS;
		i++;
	}
	if (str[i] != '\0')
		*flag = INVALID_ARGUMENTS;
	return (result);
}

int	philo_atoi(const char *str, int *flag)
{
	long long int	result;

	if (*str == '-')
	{
		str++;
		*flag = INVALID_ARGUMENTS;
		result = minus_atoi(str, flag);
	}
	else
	{
		if (*str == '+')
		{
			str++;
			*flag = INVALID_ARGUMENTS;
		}
		result = plus_atoi(str, flag);
	}
	if (result == 0)
		*flag = INVALID_ARGUMENTS;
	return (result);
}
