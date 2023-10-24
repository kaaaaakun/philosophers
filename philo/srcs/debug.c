#include "philo.h"

void	d_printf(char *msg, int nbr, char *str);
void	d_write(char *str, t_mutex *mutex_struct);

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	d_write(char *str, t_mutex *mutex_struct)
{
	pthread_mutex_lock(&mutex_struct->print);	
	write (1, str, ft_strlen(str));
	pthread_mutex_unlock(&mutex_struct->print);	
}

void d_printf(char *msg, int nbr, char *str)
{
	printf("\x1b[38;5;229m[%s", msg);
	printf("%d", nbr);
	printf("%s]\x1b[0m\n", str);
	usleep(100);
}

int	m_printf(char *msg, int nbr, int type, t_mutex *mutex_struct)
{
	long long int	ms;
	static long long int	start_time;
	static int		count;
	static int		deth_flag;

	ms = only_get_ms_time();
	if (ms == -1)
		return (-1);
	pthread_mutex_lock(&mutex_struct->print);
	if (deth_flag == 1)
		{
			pthread_mutex_unlock(&mutex_struct->print);
			return (0);
		}
	if (type == DEAD)
		deth_flag = 1;	
	if (count == 0)
	{
		start_time = ms;
		count++;
	}
	printf("\x1b[38;5;%d29m%lld %d %s\x1b[0m\n", nbr, ms - start_time, nbr, msg);
	pthread_mutex_unlock(&mutex_struct->print);
	(void)type;
	return (0);
}
