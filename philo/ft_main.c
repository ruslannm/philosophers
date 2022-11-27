/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:29:33 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 20:44:26 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	if (create_philosophers(table))
	{
		return (1);
	}
	if (create_forks(table))
	{
		free(table->philosophers);
		return (1);
	}
	table->philosopher_dead = 0;
	table->number_of_philosophers_ate = 0;
	table->start_time = get_time();
	if (pthread_mutex_init(&table->writer, NULL) != 0)
		return (1);
	return (0);
}

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&table->take_forks);
	pthread_mutex_destroy(&table->writer);
	free(table->philosophers);
	free(table->forks);
	free(table);
}

void	process_one_philosopher(t_table *table)
{
	ft_print(&table->philosophers[0], FORK);
	execute_action(table->input.time_to_die);
	ft_print(&table->philosophers[0], DIED);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (parse(argc, argv, table))
	{
		printf(USAGE);
		return (1);
	}
	if (init_table(table))
		return (1);
	if (table->input.number_of_philosophers == 1)
		process_one_philosopher(table);
	else
	{
		if (create_threads(table))
		{
			destroy_table(table);
			return (1);
		}
	}
	destroy_table(table);
	return (0);
}
