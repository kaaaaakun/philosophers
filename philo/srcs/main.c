/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:17:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/20 13:52:35 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_philo_task(t_philo_routine_data *routine_data, int *flag);
int main(int argc, char *argvi[]);

int main(int argc, char *argv[])
{
	t_philo_routine_data	*routine_data;
	int						flag;

	write (1,"AA\n",3);
	d_printf("main", argc, NULL);
	routine_data = check_args_and_make_routine_data(argc, argv);
	d_printf("main", argc, NULL);
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
	write (1,"BB\n",3);
	mutex_data = init_all_mutex_data(routine_data);
	write (1,"BB\n",3);
	//各threadの使用する関数ポインタの作成
	philo_data_arry = (t_philo_status *) malloc (sizeof(t_philo_status) * routine_data->num_of_philo);
	if (philo_data_arry == NULL)
		return (-1);
	write (1,"BB\n",3);
	//各threadの使用する関数配列にデータの差し込み
	set_data_in_philo_arry(philo_data_arry, routine_data, mutex_data);
	write (1,"BB\n",3);
	//thread用のphilo配列の作成
	philo_pthread_arry = (pthread_t *) malloc (sizeof(pthread_t) * routine_data->num_of_philo);
	if (philo_pthread_arry == NULL)
	{
		free (philo_data_arry);
		return (-1);
	}
	write (1,"BB\n",3);
	//pthreadの作成
	make_philo_threads(philo_pthread_arry, philo_data_arry, routine_data);
	d_write("bb", mutex_data);
//pthread_panoptionの作成
	set_and_make_panopticon_thread(philo_data_arry, routine_data, mutex_data);
	d_write("bb", mutex_data);
//thread joinとmutex破壊
//	join_philo_thread();
//	destroy_mutex();
    return (0);
	(void)flag;
}

