/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:36:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/18 16:37:41 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("invalid number of arguments", 2);
		return (1);
	}	
	i = 1;
	while (argv[i])
	{
		if (i == 1 && ft_atol(argv[i]) <= 0)
			return (ft_putstr_fd("invalid number of philosophers\n", 2), 1);
		else if (i == 2 && ft_atol(argv[i]) <= 0)
			return (ft_putstr_fd("invalid time to die\n", 2), 1);
		else if (i == 3 && ft_atol(argv[i]) <= 0)
			return (ft_putstr_fd("invalid time to eat\n", 2), 1);
		else if (i == 4 && ft_atol(argv[i]) <= 0)
			return (ft_putstr_fd("invalid time to sleep\n", 2), 1);
		else if (i == 5 && ft_atol(argv[i]) <= 0)
			return (ft_putstr_fd("invalid times each philo should eat\n", 2), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_program	data;

	if (validate_input(argc, argv))
		return (1);
	if (init_program(&data, argv, argc))
		return (clean_program(&data));
	philo = malloc(data.philo_n * sizeof(t_philo));
	if (!philo)
		return (clean_program(&data));
	if (init_philo(philo, &data))
		return (clean_program(&data));
	if (init_threads(philo, &data))
		return (clean_all(&data, philo));
	if (clean_all(&data, philo))
		return (1);
	return (0);
}
