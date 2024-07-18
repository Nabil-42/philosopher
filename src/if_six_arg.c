/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/18 17:14:32 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>


void	*check_philo_bis(void *params)
{
	t_para	*pa;
	int				i;
	struct timeval	now;

	pa = (t_para *)params;
	i = 0;
	pthread_mutex_lock(&pa->gate[6]);
	pa->is_dead = 0;
	pthread_mutex_unlock(&pa->gate[6]);
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	while (i < pa->nbr_philo)
		gettimeofday(&pa->philo_status[i].last_eat, NULL), ++i;
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	while (1)
	{
		usleep(500);
		pthread_mutex_lock(&pa->gate[1]);
		gettimeofday(&now, NULL);
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			printf("%ldm.s philosopher N°%d est mort de faim, il a mange le %ld et devait manger le %ld\n",
			GT(pa), i + 1, ((now.tv_sec * 1000) + (now.tv_usec / 1000))
				- ((pa->philo_status[i].last_eat.tv_sec * 1000)
					+ (pa->philo_status[i].last_eat.tv_usec / 1000)),
				pa->philo_status[i].time_to_die);
			pthread_mutex_lock(&pa->gate[6]);
			pa->is_dead = 1;
			pthread_mutex_unlock(&pa->gate[6]);
			pthread_mutex_unlock(&pa->gate[1]);
			return (NULL);
		}
		pthread_mutex_unlock(&pa->gate[1]);
		++i;
	}
}

int check_died_bis(t_para *pa, int index_p_s)
{
	
	pthread_mutex_lock(&pa->gate[6]);
	if (pa->is_dead == 1)
	{
		if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_unlock(&pa->forks[pa->nbr_philo - 1]);
	}
	else (pthread_mutex_unlock(&pa->forks[index_p_s - 1]));
	pthread_mutex_unlock(&pa->forks[index_p_s]);
		pthread_mutex_unlock(&pa->gate[6]);
		return (1);
	}
	pthread_mutex_unlock(&pa->gate[6]);
	return(0);
}
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
	init_thread(pa, &index_p_s);
	while (i < pa->must_eat)
	{
		think(pa, index_p_s);
		if(check_died(pa, index_p_s))
			return (NULL);
		give_fork(pa, index_p_s);
		if(check_died_bis(pa, index_p_s))
			return (NULL);
		take_fork(pa, index_p_s);
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
			check_philo_bis, (void *)params))
		return (printf("Error: pthread creat !"));
	pthread_mutex_unlock(&params->gate[7]);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]) + 1)
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	destroy_mutex(params, params->nbr_philo);
	free_all(params);
	return (0);
}
