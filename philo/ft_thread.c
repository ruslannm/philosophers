/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 20:50:01 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (pthread_detach(table->philosophers[i].thread_id) != 0)
			return (1);
		++i;
	}
	if (pthread_join(table->checker, NULL) != 0)
		return (1);
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

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
	if (pthread_create(&(table->checker), NULL, &checker, (void *) table))
		return (1);
	if (join_threads(table))
		return (1);
	return (0);
}
