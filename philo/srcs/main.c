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

int	main(int argc, char *argv[])
{
	t_philo_config	config;
	t_monitor		monitor;
	int				flag;

	if (make_args_config(argc, argv, &config) == false)
		return (1);
	if (init_all_data(&monitor, &config) == false)
		return (1);

	make_philo_thread()
	make_monitor_thread()
	end_of_meal()
	exec_philo_task(routine_data, &flag);
	free(routine_data);
	return (0);
}

//set_monitor
//make_philo_thread
//make_monitor_thread
//end_of_meal
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
