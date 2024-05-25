/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/05/25 13:38:59 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void check_philo(t_para *pa)
{
	int i;
	struct timeval now;

	i = 0;
	while (1)
	{
		gettimeofday(&now, NULL);
		printf("dans ma paranoiAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
		if (now.tv_usec - pa->philo_status[i].last_eat.tv_usec / 1000 > pa->time_to_die)
			(printf("philosopher N°%d est mort de faim, il a mange le %ld et devait manger le %ld\n", i + 1, now.tv_usec - pa->philo_status[i].last_eat.tv_usec / 1000, pa->time_to_die), exit(1));
		if (i == pa->nbr_philo)
			i = 0;
		++i;
	}
}

void check_philo_bis(t_para *pa)
{
	int i;
	struct timeval now;

	i = 0;
	while (1)
	{
		if (i == pa->nbr_philo - 1)
			i = 0;
		gettimeofday(&now, NULL);
		if ((now.tv_usec - pa->philo_status[i].last_eat.tv_usec) / 1000 > pa->time_to_die)
		{
		printf("philosopher N°%d est mort de faim, il a mange à %ldm.s et devait manger il y a %ldm.s\n"
			,i + 1, (now.tv_usec - pa->philo_status[i].last_eat.tv_usec) / 1000, pa->time_to_die);
		exit(1);
		}
		++i;	
	}
	exit(1);
}

void advantage(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pa->even += 2;
		printf("pa even = %d\n", pa->even);
		while(pa->even != (pa->nbr_philo + 2))
			;
	}
	if (pa->nbr_philo % 2 == 0)
	{
		
		if (pa->philo_status[index_p_s].true_id % 2 == 1)
		{
			pa->odd += 2;
			printf("pa odd = %d\n",pa->odd );
			while(pa->odd != (pa->nbr_philo + 1))
			;
			
		}
	}
	else {
		if (pa->philo_status[index_p_s].true_id % 2 == 1)
		{
			pa->odd += 2;
			while(pa->odd != ((pa->nbr_philo)))
			;
	
		}
	}
}
int befor_advantage(t_para *pa, int index_p_s)
{
	if (pa->nbr_philo % 2 == 0)
	{
		
		if (pa->philo_status[index_p_s].true_id % 2 == 0)
		{
			// printf("		Attend even avant adventage phil[%d] pa_ven = %d \n", pa->philo_status[index_p_s].true_id, pa->even);
			while (pa->philo_status[index_p_s].true_id != pa->even)
				;
			// printf("		Repart even avant adventage phil[%d]\n", pa->philo_status[index_p_s].true_id);
		}
		else {
			// printf("		Attend odd avant adventage phil[%d] pa odd = %d\n", pa->philo_status[index_p_s].true_id, pa->odd);
			while (pa->philo_status[index_p_s].true_id != pa->odd)
				;
			// printf("		Repart odd avant adventage phil[%d]\n", pa->philo_status[index_p_s].true_id);
		}
	}
	return (0);
}
int 	wait(t_para *pa, int index_p_s, int pass)
{
	pa->start_fonction++;
	while (pa->start_fonction < pa->nbr_philo)
		printf("waiting for all\n");
	if (pass == 0)
		return (1);
	if (pa->nbr_philo % 2 == 0)
	{
		
		if (pa->philo_status[index_p_s].true_id % 2 == 0)
		{
			printf("philo[%d] waiting wait in even\n", pa->philo_status[index_p_s].true_id);
			while (pa->odd != (pa->nbr_philo + 1))
				;
			pa->even = 2;
			printf("	DEBLOK philo[%d] even\n", pa->philo_status[index_p_s].true_id);

		}
		else {
			if (pass == 1)
				return (1);
			printf("		ODD PHILO [%d] waiting wait in odd\n", pa->philo_status[index_p_s].true_id);
			while (pa->even != (pa->nbr_philo + 2))
				;
			pa->odd= 1;
			printf("	DEBLOK philo[%d] odd\n", pa->philo_status[index_p_s].true_id);

		}
	}
	else {
		if (pa->philo_status[index_p_s].true_id % 2 == 0
			|| pa->philo_status[index_p_s].true_id == pa->nbr_philo)
		{
			usleep(300);
		}
	}
	return (0);
}
void *philosopher_life_bis(void *params)
{
    t_para *pa = (t_para *)params;
    struct timeval timestamp;
    int index_p_s;
    int i = 0;
    int pass = 0;

	index_p_s = pa->i;
	if (index_p_s == pa->nbr_philo)
		return(check_philo_bis(pa), NULL);
	wait(pa, index_p_s, pass);
	pass++;
    while (i < pa->must_eat)
    {
	wait(pa, index_p_s, pass);
	pass++;
        gettimeofday(&timestamp, NULL); 
        // printf("%ldm.s Philosophe %d is thinking...\n", (timestamp.tv_usec - pa->start.tv_usec) / 1000, pa->philo_status[index_p_s].true_id);
        usleep(100);
        gettimeofday(&timestamp, NULL); 
	// printf("philo [%d] has taken a fork avant lui = %d avant lui = %d\n",
	// pa->philo_status[index_p_s].true_id,pa->fork_status[index_p_s], pa->fork_status[index_p_s - 1]);
        give_fork(pa, index_p_s);
        // printf("%ldm.s Philosophe %d has taken a fork... fork = %d fork -1 = %d\n",
	// (timestamp.tv_usec - pa->start.tv_usec) / 1000, pa->philo_status[index_p_s].true_id,
	// pa->fork_status[index_p_s], pa->fork_status[index_p_s - 1]);
	// printf("%ldm.s Philosophe %d is eating...\n", (timestamp.tv_usec - pa->start.tv_usec) / 1000, pa->philo_status[index_p_s].true_id);
        usleep(pa->time_to_eat);
	gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
        give_back_fork(pa, index_p_s);
	befor_advantage(pa, index_p_s);
	advantage(pa, index_p_s);
        gettimeofday(&timestamp, NULL);
        // printf("%ldm.s Philosophe %d is sleeping...\n", (timestamp.tv_usec - pa->start.tv_usec) / 1000, pa->philo_status[index_p_s].true_id);
        usleep(pa->time_to_sleep);
	++i;  
    }

    printf("FINISHHHHH THREQD [%d]\n",pa->philo_status[index_p_s].true_id );
    return NULL;
}


int initialise_bis(char **argv, t_para params)
{	
	init(&params, argv);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
	{
		params.prio_lock[params.i] = 0;
		params.fork_status[params.i] = 0;
		params.philo_status[params.i].true_id = params.i + 1;
		pthread_mutex_init(&params.forks[params.i], NULL);
		params.i++;
	}
	params.i = 0;
	while (params.i < ft_atoi(argv[1]) + 1)
	{
		pthread_create(&params.philosophers[params.i], NULL, philosopher_life_bis, (void *)&params);
		usleep(100);
		++params.i;
	}
	usleep(10000);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
		(pthread_join(params.philosophers[params.i], NULL), ++params.i);
	params.i = 0;
	while (params.i < ft_atoi(argv[1]))
		(pthread_mutex_destroy(&params.forks[params.i]), ++params.i);
	return (0);
}
