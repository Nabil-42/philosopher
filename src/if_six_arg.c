/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_six_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:07:00 by nabil             #+#    #+#             */
/*   Updated: 2024/07/17 16:52:37 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

long	GT(t_para *pa)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((pa->start.tv_sec
				* 1000) + (pa->start.tv_usec / 1000)));
}

void	*check_philo_bis(void *params)
{
	t_para	*pa;
	int				i;
	struct timeval	now;

	pa = (t_para *)params;
	i = 0;
	usleep((1000 * (pa->nbr_philo / 2)) + (pa->time_to_die * 1000));
	while (1)
	{
		gettimeofday(&now, NULL);
		usleep(500);
		pthread_mutex_lock(&pa->gate[4]);
		if (i > pa->nbr_philo - 1)
			i = 0;
		if (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((pa->philo_status[i].last_eat.tv_sec * 1000)
				+ (pa->philo_status[i].last_eat.tv_usec
					/ 1000)) > pa->philo_status[i].time_to_die)
		{
			printf("%ldm.s philosopher N°%d est mort de faim, il a mange le %ld et devait manger le %ld\n",
			GT(pa), i + 1, ((now.tv_sec * 1000) + (now.tv_usec / 1000))
				- ((pa->philo_status[i].last_eat.tv_sec * 1000)
					+ (pa->philo_status[i].last_eat.tv_usec / 1000)),
				pa->philo_status[i].time_to_die);
			exit(1);
		}
		pthread_mutex_unlock(&pa->gate[4]);
		++i;
	}
	exit(1);
}

void	*philosopher_life_bis(void *params)
{
	t_para	*pa;
	int		index_p_s;
	int		i;

	pa = (t_para *)params;
	i = 0;
	
	pthread_mutex_lock(&pa->gate[0]);
	index_p_s = pa->i;
	pthread_mutex_unlock(&pa->gate[0]);
	
	pthread_mutex_lock(&pa->gate[7]);
	pthread_mutex_unlock(&pa->gate[7]);
	
	while (i < pa->must_eat)
	{
		pthread_mutex_lock(&pa->gate[1]);
		printf("%ldm.s Philosophe %d is thinking...\n", GT(pa),pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[1]);
		usleep(500);
		give_fork(pa, index_p_s);
		pthread_mutex_lock(&pa->gate[2]);
			printf("%ldm.s Philosophe %d has taken a fork...\n", GT(pa),pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[2]);
		pthread_mutex_lock(&pa->gate[3]);
		printf("%ldm.s Philosophe %d is eating...\n", GT(pa),pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[3]);
		usleep(pa->philo_status[index_p_s].time_to_eat * 1000);

		pthread_mutex_lock(&pa->gate[4]);
		gettimeofday(&pa->philo_status[index_p_s].last_eat, NULL);
		printf("		philo [%d] last eat = %ld\n", index_p_s + 1, GT(pa));
		pthread_mutex_unlock(&pa->gate[4]);
		
		give_back_fork(pa, index_p_s);

		pthread_mutex_lock(&pa->gate[5]);
		printf("%ldm.s Philosophe %d is sleeping...\n", GT(pa),pa->philo_status[index_p_s].true_id);
		pthread_mutex_unlock(&pa->gate[5]);
		usleep(pa->philo_status[index_p_s].time_to_sleep * 1000);
		++i;
	}
	pa->philo_status[index_p_s].finish = 1;
	printf("%ldm.s FINISHHHHH THREQD [%d]\n", GT(pa),
		pa->philo_status[index_p_s].true_id);
	return (NULL);
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

int init_mutex(t_para *params, char **argv)
{
	params->i = 0;
	while (params->i < params->nbr_philo)
	{
		mini_init_bis(params, argv);
		if (pthread_mutex_init(&params->forks[params->i], NULL))
			return (printf("Error: pthread init forks!"));
		params->i++;
	}
	params->i = 0;
	while (params->i < 10)
	{
		if (pthread_mutex_init(&params->gate[params->i], NULL))
			return (printf("Error: pthread init gate!"));
		params->i++;
	}
	return (0);
}
void destroy_mutex(t_para *params, char **argv)
{
	params->i = 0;
	while (params->i < ft_atoi(argv[1]))
		(pthread_mutex_destroy(&params->forks[params->i]), ++params->i);
	params->i = 0;
	while (params->i < 10)
		(pthread_mutex_destroy(&params->gate[params->i]), ++params->i);
}

int	initialise_bis(char **argv, t_para *params)
{
	init(params, argv);
	if (init_mutex(params, argv))
		return (1);
	params->i = 0;
	pthread_mutex_lock(&params->gate[7]);
	while (params->i < params->nbr_philo)
	{
		if (pthread_create(&params->philosophers[params->i], NULL,
				philosopher_life_bis, (void *)params))
			return (printf("Error: pthread creat !"));
		usleep(100);
		pthread_mutex_lock(&params->gate[0]);
		++params->i;
		pthread_mutex_unlock(&params->gate[0]);
	}
	gettimeofday(&params->start, NULL);
	if (pthread_create(&params->philosophers[params->i], NULL,
			check_philo_bis, (void *)params))
		return (printf("Error: pthread creat !"));
	pthread_mutex_unlock(&params->gate[7]);
	params->i = 0;
	while (params->i < ft_atoi(argv[1]))
		(pthread_join(params->philosophers[params->i], NULL), ++params->i);
	destroy_mutex(params, argv);
	return (0);
}
