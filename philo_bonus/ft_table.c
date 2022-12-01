/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:42:29 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	if (table->input.number_of_philosophers % 2)
		table->time_to_think = 10;
	else
		table->time_to_think = 0;
	table->simulation_stop = 0;
	table->start_time = get_time();
	if (create_philosophers(table))
		return (1);
	if (create_forks(table))
	{
		free(table->philosophers);
		return (1);
	}
	return (0);
}

static int	kill_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		kill(table->philosophers[i].proccess_id, SIGKILL);
		++i;
	}
	return (0);
}

void	destroy_table(t_table *table)
{
	kill_threads(table);
	sem_close(table->forks);
	sem_close(table->writer);
	sem_close(table->enough_eaten);
	sem_close(table->dead);
	free(table->philosophers);
}
