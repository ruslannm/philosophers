/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:07:19 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 16:54:51 by rgero            ###   ########.fr       */
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
	sem_close(table->writer);
	sem_close(table->forks);
	free(table->philosophers);
}
