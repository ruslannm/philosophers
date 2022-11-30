/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 16:42:26 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	table->simulation_stop = 0;
	table->start_time = get_time();
	if (create_philosophers(table))
		return (1);
	if (create_forks(table))
	{
		free(table->philosophers);
		return (1);
	}
	if (pthread_mutex_init(&table->writer, NULL) != 0)
		return (1);
	return (0);
}

static int	is_philosophers_stop(t_table *table)
{
	int			i;
	int			number_of_philosophers_stop;

	i = 0;
	number_of_philosophers_stop = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (table->philosophers[i].simulation_stop)
			++number_of_philosophers_stop;
		++i;
	}
	if (number_of_philosophers_stop == table->input.number_of_philosophers)
		return (1);
	return (0);
}

void	destroy_table(t_table *table)
{
	int	i;

	while (1)
	{
		if (is_philosophers_stop(table))
			break ;
	}
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&table->writer);
	free(table->philosophers);
	free(table->forks);
}
