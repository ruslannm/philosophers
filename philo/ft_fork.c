/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:27:48 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 20:40:52 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) \
		* table->input.number_of_philosophers);
	if (table->forks == NULL)
		return (1);
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			free(table->forks);
			return (1);
		}
		++i;
	}
	if (pthread_mutex_init(&table->take_forks, NULL) != 0)
	{
		free(table->forks);
		return (1);
	}
	return (0);
}
