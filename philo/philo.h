/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:18:33 by alli              #+#    #+#             */
/*   Updated: 2024/07/19 10:57:46 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct timeval	t_timeval;

typedef struct s_program
{
	int				philo_n;
	long long		start_time;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	int				meals_to_eat;
	bool			dead_philo_flag;
	bool			everyone_full_flag;
	bool			can_write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eating_lock;

}	t_program;

typedef struct s_philo
{
	t_program		*data;
	bool			n_philo_full;
	int				philo_index;
	long long		last_meal_time;
	int				num_meals_eaten;
	bool			all_meals_eaten;
	pthread_t		philo_thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

/*philosopher utilities*/
long		ft_atol(const char *str);
int			ft_putstr_fd(char *s, int fd);
int			ft_usleep(long long millisecond, t_philo *philo);
long long	get_current_time(void);

/*philo routine*/
void		*philo_routine(void *ptr);

/*dead or finished check*/
int			dead_or_finished(t_philo *philo);
int			starvation_check(t_philo *philo);
int			finished_meals(t_philo *philo);

/*initializing*/
int			init_philo(t_philo	*philo, t_program *data);
int			init_program(t_program *data, char **argv, int argc);
int			init_threads(t_philo *philo, t_program *data);

/*printing*/
void		print_action(t_philo *philo, char *str);
void		print_death(t_philo *philo);

/*monitoring*/
void		*monitoring(void *arg);
int			meal_check(t_program *data, t_philo *philo);
int			death_check(t_program *data, t_philo *philo);
int			check_death_flag(t_program *data);

/*clean all*/
int			clean_all(t_program *data, t_philo *philo);
int			clean_forks(int i, t_program *data);
int			clean_program(t_program *data);
#endif