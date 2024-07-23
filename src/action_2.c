/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:03:53 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/23 16:41:58 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	init_thread(t_para *pa, int *index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	if (pa->nbr_philo == 1)
		return (one_philo_life(pa), 1);
	pthread_mutex_unlock(&pa->gate[1]);
	pthread_mutex_lock(&pa->gate[0]);
	*index_p_s = pa->i;
	pthread_mutex_unlock(&pa->gate[0]);
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	if (pa->philo_status[*index_p_s].time_to_die
		< pa->philo_status[*index_p_s].time_to_sleep)
		pa->philo_status[*index_p_s].time_to_sleep
			= pa->philo_status[*index_p_s].time_to_die;
	else if (pa->philo_status[*index_p_s].time_to_die
		< pa->philo_status[*index_p_s].time_to_eat)
		pa->philo_status[*index_p_s].time_to_eat
			= pa->philo_status[*index_p_s].time_to_die;
	if (pa->philo_status[*index_p_s].true_id % 2 == 0 && pa->nbr_philo % 2 == 0)
		usleep(200);
	if (pa->nbr_philo % 2 == 1 && pa->philo_status[*index_p_s].true_id == 1)
		usleep(pa->philo_status[*index_p_s].time_to_eat * 1000);
	else if (pa->nbr_philo % 2 == 1 && pa->philo_status[*index_p_s].true_id
		% 2 == 0)
		usleep(pa->philo_status[*index_p_s].time_to_eat * 2000);
	return (0);
}

void	think_2(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is thinking\n", ge_ti(pa),
		pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	if (pa->philo_status[index_p_s].time_to_eat
		- pa->philo_status[index_p_s].time_to_sleep == 0)
		usleep(1000);
	usleep((pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep) * 1100);
}

void	think_3(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is thinking\n", ge_ti(pa),
		pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	if (pa->philo_status[index_p_s].time_to_eat
		- pa->philo_status[index_p_s].time_to_sleep == 0)
		usleep(1000);
	usleep((pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep) * 1100);
}

void	think_4(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is thinking\n", ge_ti(pa),
		pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	if (pa->philo_status[index_p_s].time_to_eat
		- pa->philo_status[index_p_s].time_to_sleep == 0)
		usleep(1000);
	usleep((pa->philo_status[index_p_s].time_to_eat
			- pa->philo_status[index_p_s].time_to_sleep) * 1100);
}

void	think(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id % 2 == 0 && pa->nbr_philo % 2 == 0)
		usleep(100);
	if (pa->nbr_philo % 2 == 1
		&& pa->philo_status[index_p_s].true_id == 1
		&& pa->philo_status[index_p_s].time_to_eat
		>= pa->philo_status[index_p_s].time_to_sleep)
	{
		think_2(pa, index_p_s);
	}
	else if (pa->nbr_philo % 2 == 1
		&& pa->philo_status[index_p_s].true_id
		% 2 == 0
		&& pa->philo_status[index_p_s].time_to_eat
		>= pa->philo_status[index_p_s].time_to_sleep)
	{
		think_3(pa, index_p_s);
	}
	else if (pa->nbr_philo % 2 == 1
		&& pa->philo_status[index_p_s].true_id
		% 2 == 1
		&& pa->philo_status[index_p_s].time_to_eat
		>= pa->philo_status[index_p_s].time_to_sleep)
	{
		think_4(pa, index_p_s);
	}
}
