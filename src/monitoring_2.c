/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:44:36 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/23 17:00:29 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	check_one_philo(t_para *pa)
{
	struct timeval	now;
	int				i;

	i = 0;
	gettimeofday(&pa->philo_status[0].last_eat, NULL);
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	while (1)
	{
		(pthread_mutex_lock(&pa->gate[1]), gettimeofday(&now, NULL));
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			(printf("%ld %d died\n", ge_ti(pa), i + 1),
				pthread_mutex_lock(&pa->gate[6]));
			pa->is_dead = 1;
			return (pthread_mutex_unlock(&pa->gate[6]),
				pthread_mutex_unlock(&pa->gate[1]), 1);
		}
		pthread_mutex_unlock(&pa->gate[1]);
		++i;
	}
}

void	check_boucle(int *k, int *j, t_para *pa)
{
	while (*k < pa->nbr_philo)
	{
		if (pa->philo_status[*k].finish == 1)
			++*j;
		++*k;
	}
}

int	boucle(int *k, int *j, t_para *pa, struct timeval now)
{
	int	i;

	i = 0;
	*k = 0;
	pthread_mutex_lock(&pa->gate[3]);
	(gettimeofday(&now, NULL), pthread_mutex_lock(&pa->gate[4]));
	check_boucle(k, j, pa);
	pthread_mutex_unlock(&pa->gate[4]);
	if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((pa->philo_status[i].last_eat.tv_sec * 1000)
			+ (pa->philo_status[i].last_eat.tv_usec
				/ 1000)) > pa->philo_status[i].time_to_die)
	{
		(pthread_mutex_lock(&pa->gate[1]), printf("%ld %d died\n", ge_ti(pa), i
				+ 1));
		(pthread_mutex_unlock(&pa->gate[1]), pthread_mutex_lock(&pa->gate[6]));
		pa->is_dead = 1;
		return (pthread_mutex_unlock(&pa->gate[6]),
			pthread_mutex_unlock(&pa->gate[3]), 0);
	}
	return (pthread_mutex_unlock(&pa->gate[3]), 1);
}

void	*check_philo_bis(void *params)
{
	t_para			*pa;
	struct timeval	now;
	int				j;
	int				k;

	pa = (t_para *)params;
	j = 0;
	k = 0;
	while (j < pa->nbr_philo)
		(gettimeofday(&pa->philo_status[j].last_eat, NULL), ++j);
	usleep((1000 * (pa->nbr_philo)) + (pa->time_to_die * 1000));
	j = 0;
	while (j < pa->nbr_philo - 1)
	{
		j = 0;
		if (boucle(&k, &j, pa, now) == 0)
			return (NULL);
	}
	pthread_mutex_unlock(&pa->gate[3]);
	return (NULL);
}

int	check_philo_2(t_para *pa)
{
	pthread_mutex_lock(&pa->gate[6]);
	pa->is_dead = 0;
	pthread_mutex_unlock(&pa->gate[6]);
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	if (pa->nbr_philo == 1)
		return (check_one_philo(pa), 1);
	if (pa->must_eat != 0)
		return (check_philo_bis(pa), 1);
	return (0);
}
