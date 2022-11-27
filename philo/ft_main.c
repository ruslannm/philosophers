/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:29:33 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 22:49:40 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (parse(argc, argv, table))
	{
		printf(USAGE);
		return (1);
	}
	if (init_table(table))
		return (1);
	if (create_threads(table))
	{
		destroy_table(table);
		return (1);
	}
	destroy_table(table);
	return (0);
}
