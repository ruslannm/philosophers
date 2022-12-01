/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:27:07 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_part_threads(t_table *table, int i)
{
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_create(&(table->philosophers[i].thread_id),
				NULL, &process, (void *) &table->philosophers[i]))
			return (1);
		pthread_detach(table->philosophers[i].thread_id);
		usleep(50);
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
	pthread_join(table->checker, NULL);
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
		if (process_execute(philosopher, table))
			break ;
	}
	return (NULL);
}

void	*checker(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	usleep((table->input.time_to_die - 5) * 1000);
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (1)
		{
			if (is_dead(table) || is_simulation_stop(table))
				break ;
			usleep(5000);
		}
	}
	else
	{
		while (1)
		{
			if (is_dead(table))
				break ;
			usleep(5000);
		}
	}
	pthread_mutex_lock(&table->writer);
	return (NULL);
}
