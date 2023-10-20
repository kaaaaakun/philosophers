#include "philo.h"

void	*routine_philo_life(void *philo_status);

void	*routine_philo_life(void *philo_status)
{
	t_philo_status *philosopher;
	philosopher = (t_philo_status *)philo_status;
	
	pthread_mutex_lock(&philosopher->mutex_struct->deth_flag_mutex);
	printf("deth_flag1i:%d",philosopher->mutex_struct->deth_flag);
	philosopher->mutex_struct->deth_flag = -1;
	printf("deth_flag2:%d",philosopher->mutex_struct->deth_flag);
	pthread_mutex_unlock(&philosopher->mutex_struct->deth_flag_mutex);

	write(1,"DD\n",3);	
	sleep(3);
	return (NULL);
	(void)philosopher;
}
