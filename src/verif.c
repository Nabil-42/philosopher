/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:57:31 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 15:38:02 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (printf("Error: Arguments are not numbers\n"));
			++j;
		}
		++i;
	}
	return (0);
}

int	verif_atoi(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || (ft_atoi(argv[i]) < INT_MIN))
			return (printf("Error: Argument > ou < INT\n"));
		++i;
	}
	return (0);
}
