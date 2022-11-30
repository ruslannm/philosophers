/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/11/29 20:11:34 by rgero            ###   ########.fr       */
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
	sem_close(&table->writer);
	sem_close(&table->forks);
	free(table->philosophers);
}
