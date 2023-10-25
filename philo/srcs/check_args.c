/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:44:04 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/25 18:06:57 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_routine_data	*check_args_and_make_routine_data(int argc, \
							char *argv[])
{
	int						flag;
	t_philo_routine_data	*routine_data;

	flag = INIT;
	if (!(argc == 5 || argc == 6))
		return (NULL);
	routine_data = (t_philo_routine_data *) malloc \
				(sizeof (t_philo_routine_data));
	if (routine_data == NULL)
		return (NULL);
	routine_data->num_of_philo = philo_atoi(argv[1], &flag);
	routine_data->time_to_die = philo_atoi(argv[2], &flag);
	routine_data->time_to_eat = philo_atoi(argv[3], &flag);
	routine_data->time_to_sleep = philo_atoi(argv[4], &flag);
	if (argc == 6)
		routine_data->number_of_times_each_philosopher_must_eat = \
			philo_atoi(argv[5], &flag);
	else
		routine_data->number_of_times_each_philosopher_must_eat = -1;
	if (flag == ARGS_ERROR)
	{	
		free(routine_data);
		routine_data = NULL;
	}
	return (routine_data);
}
