/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 22:49:08 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	table->philosopher_dead = 0;
	table->number_of_philosophers_ate = 0;
	table->start_time = get_time();
	if (create_philosophers(table))
	{
		free(table);
		return (1);
	}
	if (create_forks(table))
	{
		free(table);
		free(table->philosophers);
		return (1);
	}
	if (pthread_mutex_init(&table->take_forks, NULL) != 0)
		return (1);
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