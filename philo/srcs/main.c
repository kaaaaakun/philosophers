/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:17:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/19 20:54:18 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_philosopers(int argc, char *argv);

int main(int argc, char *argv)
{
	t_philo_routine_data	*routine_data;

	//引数のチェック
	routine_data = check_args_and_make_routine_data(argc, argv)
	if (routine_data == NULL)
		return (1);	
	exec_philosopers(routine_data);
    return (0);
	(void)argc;
	(void)argv;
}

int	exec_philo_task(t_philo_routine_data routine_data)
{
	philosophers_info	*philo_info;
	t_mutex				*mutex_data;

//哲学者の初期化
	philo_info = philosophers_and_mutex_struct_init();

//mutexの初期化
	mutex_data = init_all_mutex_data(philo_info);
	mutex_info = mutex_struct_init(phi);
    pthread_mutex_init(&print, NULL);

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
