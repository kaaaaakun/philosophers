/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:17:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/26 20:04:03 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <libc.h>

int	exec_philo_task(t_philo_routine_data *routine_data, int *flag);
int	main(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_philo_routine_data	*routine_data;
	int						flag;

	routine_data = check_args_and_make_routine_data(argc, argv);
	if (routine_data == NULL)
		return (1);
	exec_philo_task(routine_data, &flag);
	free(routine_data);
	return (0);
}

int	exec_philo_task(t_philo_routine_data *routine_data, int *flag)
{
	t_philo_status	*philo_data_arry;
	t_mutex			*mutex_data;
	pthread_t		*philo_pthread_arry;

	mutex_data = init_all_mutex_data(routine_data);
	philo_data_arry = (t_philo_status *) malloc \
					(sizeof(t_philo_status) * routine_data->num_of_philo);
	philo_pthread_arry = (pthread_t *) malloc \
						(sizeof(pthread_t) * routine_data->num_of_philo);
	if (!philo_data_arry || !mutex_data || !philo_pthread_arry)
	{
		if (mutex_data != NULL)
			free(mutex_data->fork);
		free(mutex_data);
		free (philo_data_arry);
		free (philo_pthread_arry);
		return (-1);
	}
	set_data_in_philo_arry(philo_data_arry, routine_data, mutex_data);
	make_philo_threads(philo_pthread_arry, philo_data_arry, routine_data);
	set_and_make_panopticon_thread(philo_data_arry, routine_data, mutex_data);
	join_and_destory_mutex(routine_data, philo_pthread_arry, \
			philo_data_arry, mutex_data);
	return (0);
	(void)flag;
}
//
//void	*ft_malloc(size_t size)
//{
//	void	*result;
//
//	result = (void *) malloc (size);
//	if (DEBUG == -10)
//		printf("%p/", result);
//	return (result);
//}
//
//__attribute__((destructor)) static void destructor()
//{
//    system("leaks -q philo");
//}
//
