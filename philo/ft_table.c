/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:24:44 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	if (table->input.number_of_philosophers % 2)
		table->time_to_think = 10;
	else
		table->time_to_think = 0;
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
}
