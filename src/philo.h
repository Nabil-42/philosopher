/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:35:08 by nabil             #+#    #+#             */
/*   Updated: 2024/07/15 13:54:22 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <limits.h>
#include <sys/time.h> 

typedef struct s_philo
{
    struct timeval last_eat;
    int true_id;
    int finish;
    long int time_to_sleep;
    long int time_to_eat;
    long int time_to_die;
}t_philo;

typedef struct s_para 
{
    pthread_mutex_t *forks;
    t_philo *philo_status;
    pthread_t *philosophers;
    int *fork_status;
    int must_eat;
	int nbr_philo;
    int i;
    int start_fonction;
    struct timeval start;
}t_para;

int initialise_bis(char **argv, t_para paras);
void give_fork(t_para *pa, int index_p_s);
void give_back_fork(t_para *pa, int index_p_s);
int	init(t_para *params, char **argv);
int verif_atoi(char **argv);
int verif_numbers(char **argv);
long	ft_atoi(const char *str);
void	check_philo_bis(t_para *pa);
long	GT(t_para *pa);
void	mini_init_bis(t_para *params, char **argv);
#endif