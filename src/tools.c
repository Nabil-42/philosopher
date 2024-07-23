/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 16:44:50 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

long	ge_ti(t_para *pa)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((pa->start.tv_sec
				* 1000) + (pa->start.tv_usec / 1000)));
}

void	free_all(t_para *params)
{
	if (params->philosophers)
		free(params->philosophers);
	if (params->philo_status)
		free(params->philo_status);
	if (params->forks)
		free(params->forks);
	if (params->gate)
		free(params->gate);
	if (params->fork_status)
		free(params->fork_status);
}

void	destroy_mutex(t_para *params, int nbr_philo)
{
	params->i = 0;
	while (params->i < nbr_philo)
		(pthread_mutex_destroy(&params->forks[params->i]), ++params->i);
	params->i = 0;
	while (params->i < 10)
		(pthread_mutex_destroy(&params->gate[params->i]), ++params->i);
}

void	mini_init_bis(t_para *params, char **argv)
{
	params->philo_status[params->i].time_to_sleep = ft_atoi(argv[4]);
	params->philo_status[params->i].time_to_eat = ft_atoi(argv[3]);
	params->philo_status[params->i].time_to_die = ft_atoi(argv[2]);
	params->fork_status[params->i] = 0;
	params->philo_status[params->i].finish = 0;
	params->philo_status[params->i].true_id = params->i + 1;
}

int	init(t_para *params, char **argv)
{
	params->nbr_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->start_fonction = 0;
	params->forks = malloc(params->nbr_philo * sizeof(pthread_mutex_t));
	if (params->forks == NULL)
		return (printf("Error: Malloc forks\n"));
	params->gate = malloc(10 * sizeof(pthread_mutex_t));
	if (params->gate == NULL)
		return (printf("Error: Malloc gate\n"));
	params->philo_status = malloc(params->nbr_philo * sizeof(t_philo));
	if (params->philo_status == NULL)
		return (printf("Error: Malloc philo_status\n"));
	params->philosophers = malloc((params->nbr_philo + 1) * sizeof(pthread_t));
	if (params->philosophers == NULL)
		return (printf("Error: Malloc philosophers\n"));
	params->fork_status = malloc(params->nbr_philo * sizeof(int));
	if (params->fork_status == NULL)
		return (printf("Error: Malloc fork_status\n"));
	if (argv[5] != NULL)
		params->must_eat = ft_atoi(argv[5]);
	else
		(params->must_eat = 0);
	return (0);
}
