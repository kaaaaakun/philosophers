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

int	exec_philosopers(int argc, char *argv);
void	philo_threads(t_philo_status *philo_data_arry, t_philo_routine_data *routine_data);

int main(int argc, char *argv)
{
	t_philo_routine_data	*routine_data;
	int						flag;

	routine_data = check_args_and_make_routine_data(argc, argv)
	if (routine_data == NULL)
		return (1);	
	exec_philosopers(routine_data, *flag);
	//freeの処理
	//routine_data
	//philo_data_arry
	//philo_pthread_arry
    return (0);
	(void)argc;
	(void)argv;
}

int	exec_philo_task(t_philo_routine_data routine_data, int *flag)
{
	t_philo_status	*philo_data_arry;
	t_mutex			*mutex_data;
	pthread_t		*philo_pthread_arry;

	//mutexを使用する値の初期設定
	mutex_data = init_all_mutex_data(philo_info);
	//各threadの使用する関数ポインタの作成
	philo_data_arry = (t_philo_status *) malloc (sizeof(t_philo_status) * routine_data->num_of_philo);
	if (philo_data_arry == NULL)
		return (NULL)
	//各threadの使用する関数配列にデータの差し込み
	set_data_in_philo_arry(philo_data_arry, routine_data, mutex_data);
	//thread用のphilo配列の作成
	philo_pthread_arry = (pthread_t *) malloc (sizeof(pthread_t) * routine_data->num_of_philo);
	if (philo_pthread_arry == NULL)
	{
		free (philo_data_arry);
		return (NULL);
	}
	//pthreadの作成
	make_philo_threads(philo_pthread_arry, philo_data_arry, routine_data);
	//pthread_panoptionの作成
	set_and_make_panopticon_thread(philo_data_arry, routine_data, mutex_data);

//threadの初期化
    ThreadInfo info1 = {1, &cnt, &mutex, &print};
    ThreadInfo info2 = {2, &cnt, &mutex, &print};

//threadの作成
    pthread_create(&p1, NULL, routine, (void *)&info1);
    pthread_create(&p2, NULL, routine, (void *)&info2);

//他のthreadを待つ
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

//mutexの破壊
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&print);

    return (0);
	(void)argc;
	(void)argv;

}

