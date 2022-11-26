/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:29:33 by rgero             #+#    #+#             */
/*   Updated: 2022/11/26 18:12:19 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


#include <unistd.h>
#include "philo.h"

int init_table(t_table *table){
	if (create_philosophers(table)){
		return (1);
	}
	if (create_forks(table)){
		free(table->philosophers);
		return (1);
	}
	table->philosopher_dead = 0;
	table->start_time = get_time();
	if (pthread_mutex_init(&table->writer, NULL) != 0){
		return (1);
	}
	return (0);	
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->writer);
}

void	process_one_philosopher(t_table *table)
{
	ft_print(&table->philosophers[0], FORK);
	execute_action(table->input.time_to_die);
	ft_print(&table->philosophers[0], DIED);
}

int		main(int argc, char **argv)
{
	t_table table;
	// table = malloc(sizeof(t_table));
	printf("test %p\n", &table);
    if (parse(argc, argv, &table)) {
	 	printf("Invalid input\n");
        return (1);
    }
	if (init_table(&table)) {
        return (1);
    }
	if (table.input.number_of_philosophers == 1)
	{
		printf("test\n");
		process_one_philosopher(&table);
	}
	else
	{
		if (create_threads(&table)) {
			// destroy_mutexes(&table);
			// free(table.philosophers);
			// free(table.forks);
			return (1);
		}
	}
	// destroy_mutexes(&table);
	// free(table.philosophers);
	// free(table.forks);
	return (0);
}
