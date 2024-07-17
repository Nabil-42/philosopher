/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/07/17 16:30:22 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void give_back_fork(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pa->fork_status[pa->nbr_philo - 1] = 0;
		pthread_mutex_unlock(&pa->forks[pa->nbr_philo - 1]);
		pa->fork_status[index_p_s] = 0;
		pthread_mutex_unlock(&pa->forks[index_p_s]);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 1)
	{
		pa->fork_status[index_p_s - 1] = 0;
		pthread_mutex_unlock(&pa->forks[index_p_s - 1]);
		pa->fork_status[index_p_s] = 0;
		pthread_mutex_unlock(&pa->forks[index_p_s]);
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pa->fork_status[index_p_s] = 0;
		pthread_mutex_unlock(&pa->forks[index_p_s]);
		pa->fork_status[index_p_s - 1] = 0;
		pthread_mutex_unlock(&pa->forks[index_p_s - 1]);
	}
}

void give_fork(t_para *pa, int index_p_s)
{
	
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_lock(&pa->forks[pa->nbr_philo - 1]);
		pa->fork_status[pa->nbr_philo - 1] = 1;
		pthread_mutex_lock(&pa->forks[index_p_s]);
		pa->fork_status[index_p_s] = 1;
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 1)
	{
		pthread_mutex_lock(&pa->forks[index_p_s - 1]);
		pa->fork_status[index_p_s - 1] = 1;
		pthread_mutex_lock(&pa->forks[index_p_s]);
		pa->fork_status[index_p_s] = 1;
	}
	else if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pthread_mutex_lock(&pa->forks[index_p_s]);
		pa->fork_status[index_p_s - 1] = 1;
		pthread_mutex_lock(&pa->forks[index_p_s - 1]);
		pa->fork_status[index_p_s] = 1;
	}
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
	params->philosophers = malloc((params->nbr_philo + 1)* sizeof(pthread_t));
	if (params->philosophers == NULL)
		return (printf("Error: Malloc philosophers\n"));
	params->fork_status = malloc(params->nbr_philo * sizeof(int));
	if (params->fork_status == NULL)
		return (printf("Error: Malloc fork_status\n"));
	if (argv[5] != NULL)
		params->must_eat = ft_atoi(argv[5]);
	return (0);
}

void *philosopher_life(void *params)
{
	t_para	*pa;
	int		index_p_s;
	int		i;

	pa = (t_para *)params;
	i = 0;
	pthread_mutex_lock(&pa->forks[0]);
	index_p_s = pa->i;
	pthread_mutex_unlock(&pa->forks[0]);

	if (index_p_s == pa->nbr_philo)
		return (check_philo_bis(pa), NULL);
	usleep(10000 - 100 * index_p_s); 
	while (1)
	{
		printf("%ldm.s Philosophe %d is thinking...\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		usleep(10000);
		give_fork(pa, index_p_s);
		printf("%ldm.s Philosophe %d has taken a fork...\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		printf("%ldm.s Philosophe %d is eating...\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		usleep(pa->philo_status[index_p_s].time_to_eat);
		printf("		philo [%d] last eat = %ld\n", index_p_s + 1, GT(pa));
		gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
		give_back_fork(pa, index_p_s);
		printf("%ldm.s Philosophe %d is sleeping...\n", GT(pa),
			pa->philo_status[index_p_s].true_id);
		usleep(pa->philo_status[index_p_s].time_to_sleep);
		++i;
	}
	pa->philo_status[index_p_s].finish = 1;
	return (NULL);
}


int initialise(char **argv, t_para *params)
{	
	init(params, argv);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]))
	{
		mini_init_bis(params, argv);
		pthread_mutex_init(&params->forks[params->i], NULL);
		pthread_mutex_init(&params->gate[params->i], NULL);
		usleep(1000);
		params->i++;
	}
	params->i = 0;
	while (params->i < ft_atoi(argv[1]) + 1)
	{
		if (pthread_create(&params->philosophers[params->i], NULL,
				philosopher_life, (void *)params) != 0)
			return (printf("Error: pthread creat !"));
		usleep(1000);
		pthread_mutex_lock(&params->gate[0]);
		++params->i;
		pthread_mutex_unlock(&params->gate[0]);
	}
	params->i = 0;
	while (params->i < ft_atoi(argv[1]))
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]))
		(pthread_mutex_destroy(&params->forks[params->i]), ++params->i);
	return (0);
}
int main (int argc, char **argv)
{
	t_para params;
	
	if (argc < 5 || argc > 6)
		return (printf("Erreur: Nombre d'argument\n"));
	if (verif_numbers(argv) || verif_atoi(argv))
		return (printf("Erreur: Argument non INT\n"));
	if (argc == 5)
		initialise(argv, &params);
	else (initialise_bis(argv, &params));
}