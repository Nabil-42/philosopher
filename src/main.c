/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 16:44:13 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	one_philo_life(t_para *pa)
{
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[1]);
	while (1)
	{
		think_bis(pa, 0);
		if (check_died(pa, 0))
			return ;
		give_fork_bis(pa, 0);
		if (check_died_bis(pa, 0))
			return ;
		eating_bis(pa, 0);
		usleep(pa->philo_status[0].time_to_eat * 1000);
		if (check_died_bis(pa, 0))
			return ;
		last_eat(pa, 0);
		give_back_fork(pa, 0);
		if (check_died(pa, 0))
			return ;
		sleeping_bis(pa, 0);
		if (check_died(pa, 0))
			return ;
	}
}

void	*philosopher_life(void *params)
{
	t_para	*pa;
	int		index_p_s;

	index_p_s = 0;
	pa = (t_para *)params;
	if (init_thread(pa, &index_p_s))
		return (NULL);
	while (1)
	{
		give_fork(pa, index_p_s);
		if (check_died_bis(pa, index_p_s))
			return (NULL);
		eating(pa, index_p_s);
		last_eat(pa, index_p_s);
		if (check_died_bis(pa, index_p_s))
			return (NULL);
		give_back_fork(pa, index_p_s);
		sleeping(pa, index_p_s);
		if (check_died(pa, index_p_s))
			return (NULL);
		think(pa, index_p_s);
	}
	return (NULL);
}

int	initialise(char **argv, t_para *params)
{
	if (init(params, argv) || init_mutex(params, argv))
		return (1);
	params->i = 0;
	pthread_mutex_lock(&params->gate[7]);
	while (params->i < params->nbr_philo)
	{
		if (pthread_create(&params->philosophers[params->i], NULL,
				philosopher_life, (void *)params))
			return (printf("Error: pthread creat !"));
		usleep(100);
		pthread_mutex_lock(&params->gate[0]);
		++params->i;
		pthread_mutex_unlock(&params->gate[0]);
	}
	gettimeofday(&params->start, NULL);
	if (pthread_create(&params->philosophers[params->i], NULL, check_philo,
			(void *)params))
		return (printf("Error: pthread creat !"));
	pthread_mutex_unlock(&params->gate[7]);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]) + 1)
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	(destroy_mutex(params, params->nbr_philo), free_all(params));
	return (0);
}

int	main(int argc, char **argv)
{
	t_para	params;

	if (argc < 5 || argc > 6)
		return (printf("Erreur: Nombre d'argument\n"));
	if (verif_numbers(argv) || verif_atoi(argv))
		return (printf("Erreur: Argument non INT\n"));
	if (argc == 5)
		initialise(argv, &params);
	else
		(initialise_bis(argv, &params));
}
