/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 14:50:26 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	check_died(t_para *pa, int index_p_s)
{
	(void)index_p_s;
	pthread_mutex_lock(&pa->gate[6]);
	if (pa->is_dead == 1)
	{
		pthread_mutex_unlock(&pa->gate[6]);
		return (1);
	}
	pthread_mutex_unlock(&pa->gate[6]);
	return (0);
}
void	*philosopher_life_bis(void *params)
{
	t_para	*pa;
	int		index_p_s;
	int		i;
	int		all;
	int		both;

	index_p_s = 0;
	pa = (t_para *)params;
	i = 0;
	pthread_mutex_lock(&pa->gate[1]);
	if (pa->nbr_philo == 1)
		return (one_philo_life(pa), NULL);
	pthread_mutex_unlock(&pa->gate[1]);
	init_thread(pa, &index_p_s);
	all = ((pa->philo_status[index_p_s].time_to_die
				- pa->philo_status[index_p_s].time_to_sleep
				- pa->philo_status[index_p_s].time_to_eat) / 2);
	both = (pa->philo_status[index_p_s].time_to_sleep
			+ pa->philo_status[index_p_s].time_to_eat);
	if (both < 0)
		both *= -1;
	if (all < 0)
		all *= -1;
	if (pa->philo_status[index_p_s].time_to_die < pa->philo_status[index_p_s].time_to_sleep)
		pa->philo_status[index_p_s].time_to_sleep = pa->philo_status[index_p_s].time_to_die;
	else if (pa->philo_status[index_p_s].time_to_die < pa->philo_status[index_p_s].time_to_eat)
		pa->philo_status[index_p_s].time_to_eat = pa->philo_status[index_p_s].time_to_die;
	if (pa->philo_status[index_p_s].true_id % 2 == 0 && pa->nbr_philo % 2 == 0)
		usleep((both / 2) + 50);
	if (pa->nbr_philo % 2 == 1 && pa->philo_status[index_p_s].true_id == 1)
	{
		usleep(pa->philo_status[index_p_s].time_to_eat * 1000);
	}
	else if (pa->nbr_philo % 2 == 1 && pa->philo_status[index_p_s].true_id
		% 2 == 0)
	{
		usleep(pa->philo_status[index_p_s].time_to_eat * 2000);
	}
	while (i < pa->must_eat)
	{
		give_fork(pa, index_p_s);
		if (check_died_bis(pa, index_p_s))
			return (NULL);
		eating(pa, index_p_s);
		last_eat(pa, index_p_s);
		usleep(pa->philo_status[index_p_s].time_to_eat * 1000);
		if (check_died_bis(pa, index_p_s))
			return (NULL);
		give_back_fork(pa, index_p_s);
		sleeping(pa, index_p_s);
		if (check_died(pa, index_p_s))
			return (NULL);
		think(pa, index_p_s, both);
		++i;
	}
	pthread_mutex_lock(&pa->gate[4]);
	pa->philo_status[index_p_s].finish = 1;
	pthread_mutex_unlock(&pa->gate[4]);
	return (NULL);
}

int	init_mutex(t_para *params, char **argv)
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
	if (pthread_create(&params->philosophers[params->i], NULL, check_philo,
			(void *)params))
		return (printf("Error: pthread creat !"));
	pthread_mutex_unlock(&params->gate[7]);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]) + 1)
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	destroy_mutex(params, params->nbr_philo);
	free_all(params);
	return (0);
}
