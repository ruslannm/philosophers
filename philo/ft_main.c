/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:29:33 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 11:51:44 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse(argc, argv, &table))
	{
		printf(USAGE);
		return (1);
	}
	if (init_table(&table))
		return (1);
	if (create_threads(&table))
	{
		destroy_table(&table);
		return (1);
	}
	if (pthread_join(table.checker, NULL) != 0)
		return (1);
	destroy_table(&table);
	return (0);
}
