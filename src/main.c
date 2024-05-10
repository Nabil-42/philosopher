/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:33:43 by nabil             #+#    #+#             */
/*   Updated: 2024/05/10 11:44:18 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

void philosopher_life(void *para)
{
    (pthread_mutex_t *)para;

    while (1)
    {
    printf("Philosophe pense...\n");
    usleep(time_to_think * 1000);
    printf("Philosophe a faim...\n");
    pthread_mutex_lock(&para[0]);
    pthread_mutex_lock(&para[1]);
    printf("Philosophe mange...\n");
    usleep(time_to_eat * 1000);
    pthread_mutex_unlock(&para[0]);
    pthread_mutex_unlock(&para[1]);
    printf("Philosophe dort...\n");
    usleep(time_to_sleep * 1000);    
    }
    
}

int initialise(char **argv)
{
    t_philosopherParams params;
    int num_philosopher;
    int i;


    i = 0;
    num_philosopher = ft_atoi(argv[1]);
    pthread_t philosophers[num_philosopher];
    params.forks[num_philosopher];

    while (i < num_philosopher)
        (pthread_mutex_init(&fork[i], NULL), ++i);
    i = 0;
    while (i < num_philosopher)
        (pthread_create(&philosophers[i], NULL, philosopher_life, (void *)&fork[i]), ++i);
    i = 0;
    while (i < num_philosopher)
        (pthread_join(philosophers[i], NULL), ++i);
    i = 0;
    while (i < num_philosopher)
        pthread_mutex_destroy(&fork[i]);
}
int main (int argc, char **argv)
{
    
    if (argc != 6)
        return (printf("Erreur: Nombre d'argument\n"));
    if (verif_numbers(argv) || verif_atoi(argv))
        return (printf("Erreur: Argument non INT\n"));
    initialise(argv);
}