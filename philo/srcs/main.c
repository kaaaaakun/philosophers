/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:17:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/21 19:42:17 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <libc.h>

int	exec_philo_task(t_philo_routine_data *routine_data, int *flag);
int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	t_philo_routine_data	*routine_data;
	int						flag;

	//---死なないやつ/
	argc = 5;
	argv[1] = strdup("2");
	argv[2] = strdup("2");
	argv[3] = strdup("10");
	argv[4] = strdup("10");
	//---/
	d_printf("main", argc, NULL);
	routine_data = check_args_and_make_routine_data(argc, argv);
	if (routine_data == NULL)
		return (1);	
	write (1,"AA\n",3);
	d_printf("main2", argc, NULL);
	exec_philo_task(routine_data, &flag);
	write (1,"AA\n",3);
	d_printf("main3", argc, NULL);
	//freeの処理
	//routine_data
	//philo_data_arry
	//philo_pthread_arry
	//---free
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	//-----
    return (0);
	(void)argc;
	(void)argv;
}

int	exec_philo_task(t_philo_routine_data *routine_data, int *flag)
{
	t_philo_status	*philo_data_arry;
	t_mutex			*mutex_data;
	pthread_t		*philo_pthread_arry;

	//mutexを使用する値の初期設定
	mutex_data = init_all_mutex_data(routine_data);
	//各threadの使用する関数ポインタの作成
	philo_data_arry = (t_philo_status *) malloc (sizeof(t_philo_status) * routine_data->num_of_philo);
	if (philo_data_arry == NULL)
		return (-1);
	//各threadの使用する関数配列にデータの差し込み
	set_data_in_philo_arry(philo_data_arry, routine_data, mutex_data);
	//thread用のphilo配列の作成
	philo_pthread_arry = (pthread_t *) malloc (sizeof(pthread_t) * routine_data->num_of_philo);
	if (philo_pthread_arry == NULL)
	{
		free (philo_data_arry);
		return (-1);
	}
	//pthreadの作成
	make_philo_threads(philo_pthread_arry, philo_data_arry, routine_data);
//pthread_panoptionの作成
	set_and_make_panopticon_thread(philo_data_arry, routine_data, mutex_data);
//thread joinとmutex破壊
	join_philo_thread(routine_data, philo_pthread_arry);
//	join_philo_thread();
//	destroy_mutex();
    return (0);
	(void)flag;
}

