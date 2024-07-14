/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/14 21:45:21 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// void check_philo(t_para *pa)
// {
// 	int i;

// 	i = 0;
// 	while (1)
// 	{
	
// 		printf("%ldm.s dans ma paranoiAAAAAAAAAAAAAAAAAAAAAAAAAAa\n", GT(pa));
// 		if (GT(pa) - ((pa->philo_status[i].last_eat.tv_usec / 1000)
// 		+ (pa->philo_status[i].last_eat.tv_sec * 1000)) > pa->time_to_die)
// 			(printf("%ldm.s philosopher N°%d est mort de faim, il a mange le %ld et devait manger le %ld\n",
// 				GT(pa), i + 1, GT(pa) - ((pa->philo_status[i].last_eat.tv_usec / 1000)
// 				+ (pa->philo_status[i].last_eat.tv_sec * 1000)), pa->time_to_die), exit(1));
// 		if (i == pa->nbr_philo)
// 			i = 0;
// 		++i;
// 	}
// }

long GT(t_para *pa)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000))
		- ((pa->start.tv_sec * 1000) + (pa->start.tv_usec / 1000)));
}


void check_philo_bis(t_para *pa)
{
	int i;
	struct timeval now;
	i = 0;
	usleep(50000);
	while (1)
	{
		gettimeofday(&now, NULL);
		usleep(500);
		// printf("[%d] = %ld\n", i + 1, ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - 
		// 	((pa->philo_status[i].last_eat.tv_sec * 1000) +
		// 	(pa->philo_status[i].last_eat.tv_usec / 1000)));
		// if (i == pa->nbr_philo - 1)
		// 	i = 0;
		// while (pa->philo_status[i].finish == 1)
		// 	++i;
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000)) - 
			((pa->philo_status[i].last_eat.tv_sec * 1000) +
			(pa->philo_status[i].last_eat.tv_usec / 1000)) > pa->philo_status[i].time_to_die)
		{
		printf("%ldm.s philosopher N°%d est mort de faim, il a mange le %ld et devait manger le %ld\n",
			GT(pa), i + 1, ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - 
			((pa->philo_status[i].last_eat.tv_sec * 1000) + (pa->philo_status[i].last_eat.tv_usec / 1000)), pa->philo_status[i].time_to_die);
		exit(1);
		}
		++i;
	}
	exit(1);
}

void *philosopher_life_bis(void *params)
{
    t_para *pa = (t_para *)params;
    int index_p_s;
    int i = 0;

	index_p_s = pa->i;
	if (index_p_s == pa->nbr_philo)
		return(check_philo_bis(pa), NULL);
	usleep(10000 - 100 * index_p_s);
    while (i < pa->must_eat)
    {
    printf("%ldm.s Philosophe %d is thinking...\n", GT(pa), pa->philo_status[index_p_s].true_id);
    usleep(10000);
    give_fork(pa, index_p_s);
    printf("%ldm.s Philosophe %d has taken a fork...\n", GT(pa), pa->philo_status[index_p_s].true_id);
	printf("%ldm.s Philosophe %d is eating...\n", GT(pa), pa->philo_status[index_p_s].true_id);
	usleep(pa->philo_status[index_p_s].time_to_eat);
	printf("		philo [%d] last eat = %ld\n", index_p_s + 1, GT(pa));
	gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
    give_back_fork(pa, index_p_s);    
    printf("%ldm.s Philosophe %d is sleeping...\n", GT(pa), pa->philo_status[index_p_s].true_id);
    usleep(pa->philo_status[index_p_s].time_to_sleep);
	++i; 
    }
	pa->philo_status[index_p_s].finish = 1;
	printf("%ldm.s FINISHHHHH THREQD [%d]\n", GT(pa),pa->philo_status[index_p_s].true_id );
    	return NULL;
}
void mini_init_bis(t_para *params, char **argv)
{
	params->philo_status[params->i].time_to_sleep = ft_atoi(argv[4]);
	params->philo_status[params->i].time_to_eat = ft_atoi(argv[3]);
	params->philo_status[params->i].time_to_die = ft_atoi(argv[2]);
	params->fork_status[params->i] = 0;
	params->philo_status[params->i].finish = 0;
	params->philo_status[params->i].true_id = params->i + 1;
}

int initialise_bis(char **argv, t_para params)
{	
	init(&params, argv);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
	{
		mini_init_bis(&params, argv);
		pthread_mutex_init(&params.forks[params.i], NULL);
		usleep(1000);
		params.i++;
	}
	params.i = 0;
	while (params.i < ft_atoi(argv[1]) + 1)
	{
		if (pthread_create(&params.philosophers[params.i],
			NULL, philosopher_life_bis, (void *)&params) != 0 )
			return (printf("Error: pthread creat !"));
		usleep(1000);
		++params.i;
	}
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
		(pthread_join(params.philosophers[params.i], NULL), ++params.i);
	params.i = 0;
	// while (params.i < ft_atoi(argv[1]))
	// 	(pthread_mutex_destroy(&params.forks[params.i]), ++params.i);
	return (0);
}
