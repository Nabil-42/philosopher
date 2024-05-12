/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/05/12 19:59:28 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void *philosopher_life_bis(void *params)
{
    t_para *pa = (t_para *)params;
    struct timeval timestamp;
    int index_p_s;
    int i = 0;
	
	index_p_s = pa->i;
	printf("%d\n", pa->philo_status[index_p_s].true_id);
    while (i < pa->must_eat)
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
	++i;  
    }
    return NULL;
}


int initialise_bis(char **argv)
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
		pthread_create(&params.philosophers[params.i], NULL, philosopher_life_bis, (void *)&params);
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