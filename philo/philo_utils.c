/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:53:31 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/22 11:53:33 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_usleep(long long millisecond, t_philo *philo)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < millisecond)
	{
		if (check_death_flag(philo->data))
			return (1);
		usleep(500);
	}
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		if (ft_putstr_fd("(null)", fd) == -1)
			return (-1);
		return (0);
	}
	if (write (fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}
