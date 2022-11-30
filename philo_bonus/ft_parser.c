/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:34:13 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 20:46:35 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		++i;
	}
	return (i);
}

static int	ft_atoi(char *str)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	if (ft_strlen(str) > LENGTH_INT_MAX)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		++i;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > INT_MAX)
		return (0);
	return ((int)n);
}

int	parse(int argc, char **argv, t_table *table)
{
	if (argc == 5 || argc == 6)
	{
		table->input.number_of_philosophers = ft_atoi(argv[1]);
		table->input.time_to_die = ft_atoi(argv[2]);
		table->input.time_to_eat = ft_atoi(argv[3]);
		table->input.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			table->input.number_of_times_each_philosopher_must_eat \
				= ft_atoi(argv[5]);
		else
			table->input.number_of_times_each_philosopher_must_eat = -1;
		if (!table->input.number_of_philosophers || \
			!table->input.time_to_die || !table->input.time_to_eat || \
			!table->input.time_to_sleep || \
			!table->input.number_of_times_each_philosopher_must_eat)
			return (1);
		return (0);
	}
	return (1);
}
