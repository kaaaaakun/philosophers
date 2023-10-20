#include "philo.h"

void	*routine_philo_life(void *philo_status);

void	*routine_philo_life(void *philo_status)
{
	t_philo_status *philosopher;

	philosopher = (t_philo_status *)philo_status;

	d_printf("thread",philosopher->philo_id, "");
	sleep(3);
	philosopher->eat_count = -1;
	return (NULL);
	(void)philosopher;
}
