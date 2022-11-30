/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:29:33 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 16:56:04 by rgero            ###   ########.fr       */
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
	// checker(&table);
	destroy_table(&table);
	return (0);
}
