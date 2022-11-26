/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/11/26 18:01:00 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		printf("test %d %d %d\n", table->philosophers[i].id, table->philosophers[i].fork.left, table->philosophers[i].fork.right);
        if (pthread_join(table->philosophers[i].thread_id, NULL) != 0)
			return (1);
		++i;
	}
    printf("test\n");
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
		if (pthread_create(&table->philosophers[i].thread_id,
				NULL, &process, (void *) table))
			return (1);
		++i;
	}
	if (pthread_create(&table->checker, NULL, &checker, (void *) table))
		return (1);
    printf("test\n");        
	if (join_threads(table))
		return (1);
	return (0);
}
