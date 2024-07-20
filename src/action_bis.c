/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/20 17:08:38 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>


void think_bis(t_para *pa, int index_p_s)
{
	if (index_p_s == 1)
		usleep(100);
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is thinking...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}

void eating_bis(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);
	printf("%ld %d is eating...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
}


void sleeping_bis(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[1]);

	printf("%ld %d is sleeping...\n", GT(pa),pa->philo_status[index_p_s].true_id);
	pthread_mutex_unlock(&pa->gate[1]);
	usleep(pa->philo_status[index_p_s].time_to_sleep * 1000);
}