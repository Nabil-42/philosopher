/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 14:55:23 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	init_thread(t_para *pa, int *index_p_s)
{
	pthread_mutex_lock(&pa->gate[0]);
	*index_p_s = pa->i;
	pthread_mutex_unlock(&pa->gate[0]);
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	if (pa->philo_status[*index_p_s].time_to_die < pa->philo_status[*index_p_s].time_to_sleep)
		pa->philo_status[*index_p_s].time_to_sleep = pa->philo_status[*index_p_s].time_to_die;
	else if (pa->philo_status[*index_p_s].time_to_die < pa->philo_status[*index_p_s].time_to_eat)
		pa->philo_status[*index_p_s].time_to_eat = pa->philo_status[*index_p_s].time_to_die;
	if (pa->philo_status[*index_p_s].true_id % 2 == 0 && pa->nbr_philo % 2 == 0)
		usleep(200);
	if (pa->nbr_philo % 2 == 1 && pa->philo_status[*index_p_s].true_id == 1)
	{
		usleep(pa->philo_status[*index_p_s].time_to_eat * 1000);
	}
	else if (pa->nbr_philo % 2 == 1 && pa->philo_status[*index_p_s].true_id
		% 2 == 0)
	{
		usleep(pa->philo_status[*index_p_s].time_to_eat * 2000);
	}
}

void	think(t_para *pa, int index_p_s)
{

	if (pa->philo_status[index_p_s].true_id % 2 == 0 && pa->nbr_philo % 2 == 0)
		usleep(100);
	if (pa->nbr_philo % 2 == 1 && pa->philo_status[index_p_s].true_id == 1
		&& pa->philo_status[index_p_s].time_to_eat >= pa->philo_status[index_p_s].time_to_sleep)
	{
		pthread_mutex_lock(&pa->gate[1]);
		printf("%ld %d is thinking\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[1]);
		if (pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep == 0)
			usleep(1000);
		usleep((pa->philo_status[index_p_s].time_to_eat
				- pa->philo_status[index_p_s].time_to_sleep) * 1100);
	}
	else if (pa->nbr_philo % 2 == 1 && pa->philo_status[index_p_s].true_id
		% 2 == 0
		&& pa->philo_status[index_p_s].time_to_eat >= pa->philo_status[index_p_s].time_to_sleep)
	{
		pthread_mutex_lock(&pa->gate[1]);
		printf("%ld %d is thinking\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[1]);
		if (pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep == 0)
			usleep(1000);
		usleep((pa->philo_status[index_p_s].time_to_eat
				- pa->philo_status[index_p_s].time_to_sleep) * 1100);
	}
	else if (pa->nbr_philo % 2 == 1 && pa->philo_status[index_p_s].true_id
		% 2 == 1
		&& pa->philo_status[index_p_s].time_to_eat >= pa->philo_status[index_p_s].time_to_sleep)
	{
		pthread_mutex_lock(&pa->gate[1]);
		printf("%ld %d is thinking\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[1]);
		if (pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep == 0)
			usleep(1000);
		usleep((pa->philo_status[index_p_s].time_to_eat
				- pa->philo_status[index_p_s].time_to_sleep) * 1100);
	}
}

void	take_fork_bis(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d has taken a fork\n", GT(pa),
		pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void	take_fork(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	if (check_died(pa, index_p_s))
		return (pthread_mutex_unlock(&pa->gate[1]), (void)0);
	printf("%ld %d has taken a fork\n", GT(pa),
		pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}
void	eating(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is eating\n", GT(pa), pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void	last_eat(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[3]);
	gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
	pthread_mutex_unlock(&pa->gate[3]);
	usleep(pa->philo_status[index_p_s].time_to_eat * 1000);
}

void	sleeping(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is sleeping\n", GT(pa), pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	usleep(pa->philo_status[index_p_s].time_to_sleep * 1000);
}
