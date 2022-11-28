/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/11/28 21:31:52 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_table *table)
{
	int	i;

	if (pthread_join(table->checker, NULL) != 0)
		return (1);
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_detach(table->philosophers[i].thread_id) != 0)
			return (1);
		++i;
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	if (pthread_create(&(table->checker), NULL, &checker, (void *) table))
		return (1);
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_create(&(table->philosophers[i].thread_id),
				NULL, &process, (void *) &table->philosophers[i]))
			return (1);
		i += 2;
	}
	i = 1;
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_create(&(table->philosophers[i].thread_id),
				NULL, &process, (void *) &table->philosophers[i]))
			return (1);
		i += 2;
	}
	if (join_threads(table))
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
		while (1)
		{
			if (is_dead(table) || is_simulation_stop(table))
				break ;
		}
	}
	else
	{
		while (1)
			if (is_dead(table))
				break ;
	}
	return (NULL);
}
