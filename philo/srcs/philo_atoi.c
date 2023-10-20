/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:32:37 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/19 15:55:03 by tokazaki         ###   ########.fr       */
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
		if ((l_divis == result && l_remain < str[i])
			|| l_divis < result)
			return (LONG_MAX);
		result = result * 10 + (str[i] - '0');
		if (INT_MAX < result)
			*flag = ARGS_ERROR;
		i++;
	}
	if (str[i] != '\0')
		*flag = ARGS_ERROR;
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
		if ((l_divis == result && l_remain < str[i])
			|| l_divis > result)
			return (LONG_MIN);
		result = result * 10 - (str[i] - '0');
		if (result < INT_MIN)
			*flag = ARGS_ERROR;
		i++;
	}
	if (str[i] != '\0')
		*flag = ARGS_ERROR;
	return (result);
}

int	philo_atoi(const char *str, int *flag)
{
	long long int	result;

	if (*str == '-')
	{
		str++;;
		*flag = ARGS_ERROR;
		result = minus_atoi(str, flag);
	}
	else
	{
		if (*str == '+')
		{
			str++;
			*flag = ARGS_ERROR;
		}
		result = plus_atoi(str, flag);
	}
	if (result == 0)
		*flag = ARGS_ERROR;
	return (result);
}
