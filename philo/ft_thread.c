/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 16:40:23 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_part_threads(t_table *table, int i)
{
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_create(&(table->philosophers[i].thread_id),
				NULL, &process, (void *) &table->philosophers[i]))
		{
			table->simulation_stop = 1;
			return (1);
		}
		pthread_detach(table->philosophers[i].thread_id);
		usleep(10);
		i += 2;
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	if (pthread_create(&(table->checker), NULL, &checker, (void *) table))
		return (1);
	i = 0;
	if (create_part_threads(table, 0))
		return (1);
	if (create_part_threads(table, 1))
		return (1);
	return (0);
}

void	*process(void *args)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)args;
	table = philosopher->table;
	while (1)
	{
		if (table->simulation_stop)
		{
			philosopher->simulation_stop = 1;
			break ;
		}
		if (process_execute(philosopher, table))
			break ;
	}
	return (NULL);
}

void	*checker(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (table->simulation_stop == 0)
		{
			if (is_dead(table) || is_simulation_stop(table))
				break ;
		}
	}
	else
	{
		while (table->simulation_stop == 0)
		{
			if (is_dead(table))
				break ;
		}
	}
	return (NULL);
}
