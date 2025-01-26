# philosophers

Philosophers is a C programming project that simulates the Dining Philosophers Problem using multithreading and mutexes, 
requiring synchronization mechanisms to avoid deadlocks while precisely managing competition between multiple philosophers (threads) for shared resources (forks).

### Installing

Clone the repository and `make`.

### Running

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]  the last one is optional

  `./philo 4 410 200 200 4` 


### rules for the project

1. Philosophers sit around a circular table with a bowl of spaghetti at the center. 
2. Forks (equal in number to the philosophers) are placed to the right of each philosopher.
3. Each philosopher alternates between three actions: thinking, eating, and sleeping, with parameters specifying durations (in milliseconds) for eating and sleeping.
4. If a philosopher exceeds the time_to_die limit without eating, the philo dies.
5. To eat, a philosopher must use two forks (both the left and right ones).
6. The simulation ends immediately if any philosopher dies.
7. If the optional number_of_times_each_philosopher_must_eat is provided, the simulation also ends once all philosophers have eaten the specified number of times.
