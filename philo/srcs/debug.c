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

	pthread_mutex_lock(&mutex_struct->print);	
	ms = get_ms_time();
	if (ms == -1)
		return (-1);
	printf("\x1b[38;5;%d29m", nbr);
	printf("%lld ", ms);
	printf("%d ", nbr);
	printf("%s", msg);
	printf("\x1b[0m\n");
	pthread_mutex_unlock(&mutex_struct->print);	
	(void)type;
	return (0);
}
