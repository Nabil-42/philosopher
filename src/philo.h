/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:35:08 by nabil             #+#    #+#             */
/*   Updated: 2024/05/12 19:37:25 by nabil            ###   ########.fr       */
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
    struct timeval last_eat, current_time;
    int true_id;
}t_philo;

typedef struct s_para 
{
    pthread_mutex_t *forks;
    t_philo *philo_status;
    pthread_t *philosophers;
    int *fork_status;
    int time_to_sleep;
    int time_to_eat;
    int time_to_die;
    int must_eat;
    int nbr_philo;
    int i;
}t_para;

int initialise_bis(char **argv);
void give_fork(t_para *pa, int index_p_s);
void give_back_fork(t_para *pa, int index_p_s);
int	init(t_para *params, char **argv);
int verif_atoi(char **argv);
int verif_numbers(char **argv);
long	ft_atoi(const char *str);

#endif