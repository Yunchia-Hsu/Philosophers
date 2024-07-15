/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:18:41 by alli              #+#    #+#             */
/*   Updated: 2024/07/15 12:57:29 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long millisecond)
{
	size_t start;
	size_t relapse;
	
	start = get_current_time();
	relapse = get_current_time() - start;
	while (relapse < millisecond)
		usleep(500);//可以讓操作系統有機會調度其他任務
}

size_t get_current_time(void)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("Error: getimeof day failed\n", 2);	
	return (time.tv_usec * 1000 + time.tv_usec / 1000);
}
// int	safe_mutex_lock(pthread_mutex_t *str)
// {
// 	if (pthread_mutex_lock(str))
// 	{
// 		//clean all
// 		return (1);
// 	}
// 	return (0);
// }

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (! s)
	{
		if (ft_putstr_fd("(null)", fd) == -1)
			return (-1);
		return (0);
	}
	if (write (fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_longint(long num, int dig)
{
	long long	llong_max;

	llong_max = 9223372036854775807;
	if (num > llong_max / 10)
		return (1);
	else if (num * 10 > llong_max - dig)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int				sign;
	long			total;
	int				i;

	sign = 1;
	total = 0;
	i = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (((str[i] == '+') || str[i] == '-') && str[i])
	{
		if (str[i] == '-')
			sign = 0;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		if (check_longint(total, str[i] - '0'))
			return (sign * -1);
		total = total * 10 + (str[i++] - '0');
	}
	if (!sign)
		total = total * -1;
	return (total);
}