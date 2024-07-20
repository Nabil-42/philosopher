/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/20 17:16:22 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>




int check_died(t_para *pa, int index_p_s)
{
	(void)index_p_s;
	pthread_mutex_lock(&pa->gate[6]);
	if (pa->is_dead == 1)
	{
		pthread_mutex_unlock(&pa->gate[6]);
		return (1);
	}
	pthread_mutex_unlock(&pa->gate[6]);
	return(0);
}
void	*philosopher_life_bis(void *params)
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
	while (i < pa->must_eat)
	{
		think(pa, index_p_s);
		if(check_died(pa, index_p_s))
			return (NULL);
		give_fork(pa, index_p_s);
		if(check_died_bis(pa, index_p_s))
			return (NULL);
		eating(pa, index_p_s);
		usleep(pa->philo_status[index_p_s].time_to_eat * 1000);
		if(check_died_bis(pa, index_p_s))
			return (NULL);
		last_eat(pa, index_p_s);
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


int init_mutex(t_para *params, char **argv)
{
	params->i = 0;
	while (params->i < params->nbr_philo)
	{
		mini_init_bis(params, argv);
		if (pthread_mutex_init(&params->forks[params->i], NULL))
			return (printf("Error: pthread init forks!"));
		params->i++;
	}
	params->i = 0;
	while (params->i < 10)
	{
		if (pthread_mutex_init(&params->gate[params->i], NULL))
			return (printf("Error: pthread init gate!"));
		params->i++;
	}
	return (0);
}


int	initialise_bis(char **argv, t_para *params)
{
	init(params, argv);
	if (init_mutex(params, argv))
		return (1);
	params->i = 0;
	pthread_mutex_lock(&params->gate[7]);
	while (params->i < params->nbr_philo)
	{
		if (pthread_create(&params->philosophers[params->i], NULL,
				philosopher_life_bis, (void *)params))
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
