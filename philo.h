
#ifndef PHILO_H
# define PHILO_H

//write, usleep
# include <unistd.h>
//malloc, free
#include <stdlib.h>
//memset
# include <string.h>
//printf 
# include <stdio.h>
//pthread, mutex
# include <pthread.h>
//gettimeofday
# include <sys/time.h>


typedef struct s_philo
{
    pthread_t t;
    int philo_n;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	meals_to_eat;
} t_philo


typedef struct s_program
{
    int dead;
    int *philo;
    //   3   pthread_mutex_t 
    pthread_mutex_t l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	eating_lock;
} t_program

/*philosopher utilities*/
int	ft_atoi(const char *str);






#endif