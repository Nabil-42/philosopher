/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:15:50 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/22 18:07:23 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int check_one_philo(t_para *pa)
{
	struct timeval	now;
	int i = 0;
	
	gettimeofday(&pa->philo_status[0].last_eat, NULL);
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	while (1)
	{
		pthread_mutex_lock(&pa->gate[1]);
		gettimeofday(&now, NULL);
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			printf("%ld %d died\n", GT(pa), i + 1);
			pthread_mutex_lock(&pa->gate[6]);
			pa->is_dead = 1;
			pthread_mutex_unlock(&pa->gate[6]);
			pthread_mutex_unlock(&pa->gate[1]);
			return 0;
		}
		pthread_mutex_unlock(&pa->gate[1]);
		++i;
	}
}

void	*check_philo_bis(void *params)
{
	t_para	*pa;
	int				i;
	int				j;
	int				k;
	struct timeval	now;

	pa = (t_para *)params;
	i = 0;
	j = 0;
	k = 0;

	while (j < pa->nbr_philo)
		gettimeofday(&pa->philo_status[j].last_eat, NULL), ++j;
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	j = 0;
	while (1)
	{
		pthread_mutex_lock(&pa->gate[3]);
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&pa->gate[4]);
		k = 0;
		while (pa->philo_status[i].finish == 1 && i <= pa->nbr_philo)
			++i, ++k;
		if (i > pa->nbr_philo - 1)
			i = 0;
		pthread_mutex_unlock(&pa->gate[4]);
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			
			pthread_mutex_lock(&pa->gate[1]);
			printf("%ld %d died\n", GT(pa), i + 1);
			pthread_mutex_unlock(&pa->gate[1]);
			pthread_mutex_lock(&pa->gate[6]);
			pa->is_dead = 1;
			pthread_mutex_unlock(&pa->gate[6]);
			pthread_mutex_unlock(&pa->gate[3]);
			return (NULL);
		}
		pthread_mutex_unlock(&pa->gate[3]);
		if (k == pa->nbr_philo)
			break;
		++j;
	}
	return (NULL);
}

void	*check_philo(void *params)
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
	if (pa->nbr_philo == 1)
		return (check_one_philo(pa), NULL);
	if (pa->must_eat != 0)
		return (check_philo_bis(pa), NULL);
	while (i < pa->nbr_philo)
		gettimeofday(&pa->philo_status[i].last_eat, NULL), ++i;
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	while (1)
	{
		pthread_mutex_lock(&pa->gate[3]);
		gettimeofday(&now, NULL);
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			pthread_mutex_lock(&pa->gate[1]);
			printf("%ld %d died\n", GT(pa), i + 1);
			pthread_mutex_unlock(&pa->gate[1]);
			pthread_mutex_lock(&pa->gate[6]);
			pa->is_dead = 1;
			pthread_mutex_unlock(&pa->gate[6]);
			pthread_mutex_unlock(&pa->gate[3]);
			return (NULL);
		}
		pthread_mutex_unlock(&pa->gate[3]);
		++i;
	}
}

int check_died_bis(t_para *pa, int index_p_s)
{
	pthread_mutex_lock(&pa->gate[6]);
	if (pa->is_dead == 1 && pa->nbr_philo != 1)
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
	else if (pa->nbr_philo == 1)
	{
		pthread_mutex_unlock(&pa->forks[index_p_s]);
		pthread_mutex_unlock(&pa->gate[6]);
		return (1);
	}
	pthread_mutex_unlock(&pa->gate[6]);
	return(0);
}