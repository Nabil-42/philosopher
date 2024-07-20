/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/07/20 17:25:07 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void one_philo_life(t_para *pa)
{
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[1]);
	while (1)
	{
		think_bis(pa, 0);
		if(check_died(pa, 0))
			return ;
		give_fork_bis(pa, 0);
		if(check_died_bis(pa, 0))
			return ;
		eating_bis(pa, 0);
		usleep(pa->philo_status[0].time_to_eat * 1000);
		if(check_died_bis(pa, 0))
			return ;
		last_eat(pa, 0);
		give_back_fork(pa, 0);
		if(check_died(pa, 0))
			return ;
		sleeping_bis(pa, 0);
		if(check_died(pa, 0))
			return ;
	}
}

void *philosopher_life(void *params)
{
	t_para	*pa;
	int		index_p_s;
	int		i;
	
	index_p_s = 0;
	pa = (t_para *)params;
	i = 0;
	pthread_mutex_lock(&pa->gate[1]);
	if (pa->nbr_philo == 1)
		return (one_philo_life(pa), NULL);
	pthread_mutex_unlock(&pa->gate[1]);
	init_thread(pa, &index_p_s);
	while (1)
	{
		think(pa, index_p_s);
		if(check_died(pa, index_p_s))
			return (NULL);
		give_fork(pa, index_p_s);
		if(check_died_bis(pa, index_p_s))
			return (NULL);
		eating(pa, index_p_s);
		last_eat(pa, index_p_s);
		usleep(pa->philo_status[index_p_s].time_to_eat * 1000);
		if(check_died_bis(pa, index_p_s))
			return (NULL);
		give_back_fork(pa, index_p_s);
		if(check_died(pa, index_p_s))
			return (NULL);
		sleeping(pa, index_p_s);
		if(check_died(pa, index_p_s))
			return (NULL);
		++i;
	}
	return (NULL);
}


int initialise(char **argv, t_para *params)
{	
	init(params, argv);
	if (init_mutex(params, argv))
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
	if (pthread_create(&params->philosophers[params->i], NULL,
			check_philo, (void *)params))
		return (printf("Error: pthread creat !"));
	pthread_mutex_unlock(&params->gate[7]);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]) + 1)
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	destroy_mutex(params, params->nbr_philo);
	free_all(params);
	return (0);
}

int main (int argc, char **argv)
{
	t_para params;
	
	if (argc < 5 || argc > 6)
		return (printf("Erreur: Nombre d'argument\n"));
	if (verif_numbers(argv) || verif_atoi(argv))
		return (printf("Erreur: Argument non INT\n"));
	if (argc == 5)
		initialise(argv, &params);
	else (initialise_bis(argv, &params));
}