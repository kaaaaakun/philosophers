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

#define INIT 0
#define INVALID_ARGUMENTS 1

static bool	*print_error(void);
static bool	set_args_config(int argc, char *argv[], t_philo_config *config);
bool		make_philo_config(int argc, char *argv[], t_philo_config *config);

bool	make_philo_config(int argc, char *argv[], t_philo_config *config)
{
	if (!(argc == 5 || argc == 6))
		return (print_error());
	// config = (t_philo_config *) ft_malloc (sizeof (t_philo_config));
	// if (config == NULL)
	// 	return (print_error());
	if (set_args_config(argc, argv, config) == INVALID_ARGUMENTS)
	{	
		//free(config);
		config = NULL;
		return (print_error());
	}
	return (true);
}

static bool	set_args_config(int argc, char *argv[], t_philo_config *config)
{
	int	parse_error;

	parse_error = INIT;
	config->num_philo = philo_atoi(argv[1], &parse_error);
	config->die_time = philo_atoi(argv[2], &parse_error);
	config->eat_time = philo_atoi(argv[3], &parse_error);
	config->sleep_time = philo_atoi(argv[4], &parse_error);
	config->start_time = get_ms_time() + 300;
	config->has_option = false;
	if (argc == 6)
	{
		config->must_eat_count = philo_atoi(argv[5], &parse_error);
		config->has_option = true;
	}
	return (parse_error);
}

static bool	*print_error(void)
{
	printf("ERROR\n");
	return (false);
}
