/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:58:11 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 14:50:11 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_back_fork(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_unlock(&pa->forks[pa->nbr_philo - 1]);
		pthread_mutex_unlock(&pa->forks[index_p_s]);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 1)
	{
		pthread_mutex_unlock(&pa->forks[index_p_s - 1]);
		pthread_mutex_unlock(&pa->forks[index_p_s]);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pthread_mutex_unlock(&pa->forks[index_p_s]);
		pthread_mutex_unlock(&pa->forks[index_p_s - 1]);
	}
}

void	give_fork_bis(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_lock(&pa->forks[index_p_s]);
		take_fork_bis(pa, index_p_s);
	}
}

void	give_fork(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_lock(&pa->forks[pa->nbr_philo - 1]);
		take_fork(pa, index_p_s);
		pthread_mutex_lock(&pa->forks[index_p_s]);
		take_fork(pa, index_p_s);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 1)
	{
		pthread_mutex_lock(&pa->forks[index_p_s - 1]);
		take_fork(pa, index_p_s);
		pthread_mutex_lock(&pa->forks[index_p_s]);
		take_fork(pa, index_p_s);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pthread_mutex_lock(&pa->forks[index_p_s]);
		take_fork(pa, index_p_s);
		pthread_mutex_lock(&pa->forks[index_p_s - 1]);
		take_fork(pa, index_p_s);
	}
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	i;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
