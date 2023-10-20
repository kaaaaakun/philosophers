#include "philo.h"

void d_printf(char *msg, int nbr, char *str);

void d_printf(char *msg, int nbr, char *str)
{
	printf("\x1b[38;5;229m[%s", msg);
	printf("%d", nbr);
	printf("%s]\x1b[0m", str);
	usleep(100);
}
