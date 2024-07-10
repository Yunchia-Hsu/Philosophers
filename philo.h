
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




//philo:   5人 800死 200吃 200睡覺  

typedef struct s_philo
{
    pthread_t t;
    int philo_n;//id
    long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
    long last_eat_time;//use long because we use millm isecond
    pthread_t thread_id;

} t_philo;


typedef struct s_program
{
    bool dead;
    int *philo;
    int fork_id; //for debug
    
    //   3   pthread_mutex_t 
    pthread_mutex_t l_fork;
    pthread_mutex_t r_fork;
    pthread_mutex_t eating_lock;
    t_philo *philos;
} t_program








#endif