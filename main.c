
#include "philo.h"

//check_status

//check_philo_number

//int clean_all(t_program *data, char **argv)


int monitor_die()
{

//infinite loop until philo dies
//check die; time now - last meal < the time philo needs to die

}


int routine(t_program *data, char **argv)// 睡 思考 吃
{
    //loop the routine, and break when dead flag is 1
    //sleeping   ft_usleep (modified usleep for sleep)
    // thinking: print message
    //eating : ft_usleep , print message , update last_eat_time
    //    lock right / left forks , ft_usleep, drop forks (unlock fork)

    //destroy mutex; free data if allocate any
}


int init_philo(int argc, char **argv)
{

}

ft_purstr_fd
     
int validate_input(int argc, char **argv)
{
    //./philo 5 philo ;800 time to die ;200 time to eat ;200 time to sleep
    int i;

    if (argc != 5 && argc != 6)
    {
        ft_purstr_fd("invalid number of arguments", 2);
        return (1);
    }
    i = 1;
    while (argv[i])
    {
        if (i == 1 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid number of philosophers"), 1);
        else if (i == 2 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to die", 2), 1);
        else if (i == 3 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to eat", 2), 1);
        else if (i == 4 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to sleep", 2), 1);
        else if (i == 5 && atol(argv[i]) < 0)
            return (ft_putstr_fd("invalid times each philo should eat", 2), 1);
        i++;
    }
    return (0);
}

//./philo 5人 800死 200吃 200睡覺 
int main(int argc, char *argv[])
{
    //number_of_philosophers time_to_die time_to_eat time_to_sleep
    t_program data;

    //valid input  The number of philosophers , The time a philosopher will die if he doesn’t eat , The time it takes a philosopher to eat , The time it takes a philosopher to sleep   > 0   philo < 200
    if (validate_input(argc, argv))
        return (1);
    
    if (init_program(&data, argv))
        return (1);
    
     
    threads();
    /* run threads: 
    1. create philo and check threads and run routine ; every philo is a thread  create threads
    2. monitor- if die thread 
    3. monitor-if full thread
    4.threads join 
   
    */
   
    
    //monitor die 

    // monitor full

    if (clean_all(&data, argv))
        return (1);
    
    return (0);
}


/*
log:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/