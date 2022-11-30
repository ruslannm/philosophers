/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:27:48 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 20:38:32 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_table *table)
{
	int	i;

	sem_unlink("/philo_bonus_forks");
	sem_unlink("/philo_bonus_writer");
	sem_unlink("/philo_bonus_enough_eaten");
	sem_unlink("/philo_bonus_dead");
	table->forks = sem_open("/philo_bonus_forks", O_CREAT, S_IRWXU, \
		table->input.number_of_philosophers);
	table->writer = sem_open("/philo_bonus_writer", O_CREAT, S_IRWXU, 1);
	table->enough_eaten = sem_open("/philo_bonus_enough_eaten", O_CREAT, \
		S_IRWXU, table->input.number_of_philosophers);
	table->dead = sem_open("/philo_bonus_dead", O_CREAT, S_IRWXU, \
		table->input.number_of_philosophers + 1);
	if (table->forks == SEM_FAILED || table->writer == SEM_FAILED || \
		table->enough_eaten == SEM_FAILED || table->dead == SEM_FAILED)
		return (1);
	i = -1;
	while (++i <= table->input.number_of_philosophers)
		sem_wait(table->dead);
	i = -1;
	while (++i < table->input.number_of_philosophers)
		sem_wait(table->enough_eaten);
	return (0);
}
