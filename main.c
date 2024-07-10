#include "philo.h"

//valid input  The number of philosophers , The time a philosopher will die if he doesn’t eat , The time it takes a philosopher to eat , The time it takes a philosopher to sleep   > 0   philo < 200
init_program
init_philo
//every philo is a thread  create threads; monitor is also a thread

// each philo geos into the routine function
// eat , sleep, think
routine()
{
    //loop the routine, and break when dead flag is 1
    // thinking: print message
    //eating : ft_usleep , print message
    //sleep :lock right / left forks , printf message , ft_usleep, drop forks (unlock fork)

    //destroy mutex; free data if allocate any
}

monitor()
{

//infinite loop until philo dies
//check die; time now - last meal < the time philo needs to die

}


/*
log:
X is thinking
X is sleeping
X is eating
*/