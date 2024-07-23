/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:35:08 by nabil             #+#    #+#             */
/*   Updated: 2024/07/23 14:51:21 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bsd/string.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct timeval	last_eat;
	int				true_id;
	int				finish;
	long int		time_to_sleep;
	long int		time_to_eat;
	long int		time_to_die;
}					t_philo;

typedef struct s_para
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*gate;
	t_philo			*philo_status;
	pthread_t		*philosophers;
	int				*fork_status;
	int				must_eat;
	int				nbr_philo;
	int				i;
	int				start_fonction;
	long int		time_to_die;
	int				is_dead;
	struct timeval	start;
}					t_para;

void				take_fork_bis(t_para *pa, int index_p_s);
void				give_fork_bis(t_para *pa, int index_p_s);
void				sleeping_bis(t_para *pa, int index_p_s);
void				eating_bis(t_para *pa, int index_p_s);
void				think_bis(t_para *pa, int index_p_s);
void				one_philo_life(t_para *pa);
int					check_one_philo(t_para *pa);
void				eating(t_para *pa, int index_p_s);
int					check_died_bis(t_para *pa, int index_p_s);
int					init_mutex(t_para *params, char **argv);
int					check_died(t_para *pa, int index_p_s);
int					initialise(char **argv, t_para *params);
int					init(t_para *params, char **argv);
void				mini_init_bis(t_para *params, char **argv);
void				free_all(t_para *params);
void				destroy_mutex(t_para *params, int nbr_philo);
int					initialise_bis(char **argv, t_para *paras);
void				give_fork(t_para *pa, int index_p_s);
void				give_back_fork(t_para *pa, int index_p_s);
int					init(t_para *params, char **argv);
int					verif_atoi(char **argv);
int					verif_numbers(char **argv);
long				ft_atoi(const char *str);
void				*check_philo(void *params);
long				GT(t_para *pa);
void				mini_init_bis(t_para *params, char **argv);

void				init_thread(t_para *pa, int *index_p_s);
void				think(t_para *pa, int index_p_s);
void				take_fork(t_para *pa, int index_p_s);
void				last_eat(t_para *pa, int index_p_s);
void				sleeping(t_para *pa, int index_p_s);

#endif