/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/20 17:51:57 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>



void init_thread(t_para *pa, int *index_p_s)
{
	pthread_mutex_lock(&pa->gate[0]);
	*index_p_s = pa->i;
	pthread_mutex_unlock(&pa->gate[0]);
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
}

void think(t_para *pa, int index_p_s)
{
	if (index_p_s == 1)
		usleep(100);
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is thinking...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void take_fork_bis(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d has taken a fork...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void take_fork(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	if(check_died(pa, index_p_s))
			return (pthread_mutex_unlock(&pa->gate[1]), (void)0);
	printf("%ld %d has taken a fork...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}
void eating(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is eating...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void last_eat(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
	pthread_mutex_unlock(&pa->gate[1]);
}

void sleeping(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is sleeping...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	usleep(pa->philo_status[index_p_s].time_to_sleep * 1000);
}