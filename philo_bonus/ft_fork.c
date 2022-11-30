/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:27:48 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 12:02:07 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_table *table)
{
	sem_unlink("/philo_bonus_forks");
	sem_unlink("/philo_bonus_writer");
	sem_unlink("/philo_bonus_enough_eaten");
	sem_unlink("/philo_bonus_dead");
	table->forks = sem_open("/philo_bonus_forks", O_CREAT, S_IRWXU, \
		table->input.number_of_philosophers);
	table->writer = sem_open("/philo_bonus_writer", O_CREAT, S_IRWXU, 1);
	table->enough_eaten = sem_open("/philo_bonus_enough_eaten", O_CREAT, \
		S_IRWXU, 0);
	table->dead = sem_open("/philo_bonus_dead", O_CREAT, S_IRWXU, 0);
	if (table->forks <= 0 || table->writer <= 0 || table->enough_eaten || \
		table->dead)
		return (1);
	return (0);
}
