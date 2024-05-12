/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/05/12 19:57:17 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void give_back_fork(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		pthread_mutex_unlock(&pa->forks[index_p_s]);
		pthread_mutex_unlock(&pa->forks[pa->nbr_philo - 1]);
		pa->fork_status[index_p_s] = 0;
		pa->fork_status[pa->nbr_philo - 1] = 0;
	}
	else {
		pthread_mutex_unlock(&pa->forks[index_p_s]);
		pthread_mutex_unlock(&pa->forks[index_p_s - 1]);
		pa->fork_status[index_p_s] = 0;
		pa->fork_status[index_p_s - 1] = 0;
	}
}

void give_fork(t_para *pa, int index_p_s)
{
	
	if (pa->philo_status[index_p_s].true_id == 1)
	{
		while(pa->fork_status[index_p_s] == 1 &&
			pa->fork_status[pa->nbr_philo - 1] == 1)
				;
		pa->fork_status[index_p_s] = 1;
		pa->fork_status[pa->nbr_philo - 1] = 1;
		printf("if %d\n", pa->philo_status[index_p_s].true_id);
		pthread_mutex_lock(&pa->forks[index_p_s]);
		pthread_mutex_lock(&pa->forks[pa->nbr_philo - 1]);
	}
	else {
		while(pa->fork_status[index_p_s] == 1 &&
			pa->fork_status[index_p_s - 1] == 1)
				;
		printf("else %d\n", pa->philo_status[index_p_s].true_id);
		pa->fork_status[index_p_s] = 1;
		pa->fork_status[index_p_s - 1] = 1;
		pthread_mutex_lock(&pa->forks[index_p_s]);
		pthread_mutex_lock(&pa->forks[index_p_s - 1]);
	}
}
int	init(t_para *params, char **argv)
{
	params->nbr_philo = ft_atoi(argv[1]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_die = ft_atoi(argv[2]);
	params->forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (params->forks == NULL)
		return (printf("Error: Malloc forks\n"));
	params->philo_status = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (params->philo_status == NULL)
		return (printf("Error: Malloc philo_status\n"));
	params->philosophers = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	if (params->philosophers == NULL)
		return (printf("Error: Malloc philosophers\n"));
	params->fork_status = malloc(ft_atoi(argv[1]) * sizeof(int));
	if (params->fork_status == NULL)
		return (printf("Error: Malloc fork_status\n"));
	if (argv[5] != NULL)
		params->must_eat = ft_atoi(argv[5]);
	return (0);
}

void *philosopher_life(void *params)
{
    t_para *pa = (t_para *)params;
    struct timeval timestamp;
	int index_p_s;
	
	index_p_s = pa->i;
	printf("%d\n", pa->philo_status[index_p_s].true_id);
	sleep(3);
    while (1)
    {
        gettimeofday(&timestamp, NULL); 
        printf("%ld Philosophe %d is thinking...\n", timestamp.tv_sec, pa->philo_status[index_p_s].true_id);
        usleep( 1000);
        gettimeofday(&timestamp, NULL); 
        printf("%ld Philosophe %d has taken a fork...\n", timestamp.tv_sec, pa->philo_status[index_p_s].true_id);
        give_fork(pa, index_p_s);
		printf("%ld Philosophe %d is eating...\n", timestamp.tv_sec, pa->philo_status[index_p_s].true_id);
        usleep(pa->time_to_eat);
		gettimeofday(&pa->philo_status->last_eat, NULL);
        give_back_fork(pa, index_p_s);
        gettimeofday(&timestamp, NULL);
        printf("%ld Philosophe %d is sleeping...\n", timestamp.tv_sec, pa->philo_status[index_p_s].true_id);
        usleep(pa->time_to_sleep);  
    }
}


int initialise(char **argv)
{
	t_para params;
	
	init(&params, argv);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
	{
		params.fork_status[params.i] = 0;
		params.philo_status[params.i].true_id = params.i + 1;
		pthread_mutex_init(&params.forks[params.i], NULL);
		params.i++;
	}
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
	{
		pthread_create(&params.philosophers[params.i], NULL, philosopher_life, (void *)&params);
		sleep(1);
		++params.i;
	}
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
		(pthread_join(params.philosophers[params.i], NULL), ++params.i);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
		(pthread_mutex_destroy(&params.forks[params.i]), ++params.i);
	return (0);
}
int main (int argc, char **argv)
{
	
	if (argc < 5 || argc > 6)
		return (printf("Erreur: Nombre d'argument\n"));
	if (verif_numbers(argv) || verif_atoi(argv))
		return (printf("Erreur: Argument non INT\n"));
	if (argc == 5)
		initialise(argv);
	else (initialise_bis(argv));
}