
void advantage(t_para *pa, int index_p_s)
{
	if (pa->philo_status[index_p_s].true_id % 2 == 0)
	{
		pa->even += 2;
		printf("%ldm.s pa even = %d\n", GT(pa), pa->even);
		while(pa->even != (pa->nbr_philo + 2))
			;
	}
	if (pa->nbr_philo % 2 == 0)
	{
		if (pa->philo_status[index_p_s].true_id % 2 == 1)
		{
			pa->odd += 2;
			printf("%ldm.s pa odd = %d\n", GT(pa),pa->odd );
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
			printf("%ldm.s 		Attend even avant adventage phil[%d] pa_ven = %d \n", GT(pa), pa->philo_status[index_p_s].true_id, pa->even);
			while (pa->philo_status[index_p_s].true_id != pa->even)
						;
			printf("%ldm.s 		Repart even avant adventage phil[%d]\n", GT(pa), pa->philo_status[index_p_s].true_id);
			// (printf("%ld philo[%d] wait BEFOR ADVANTAGE even = %d\n", GT(pa), pa->philo_status[index_p_s].true_id, pa->even));
		}
		else {
			printf("%ldm.s 		Attend odd avant adventage phil[%d] pa odd = %d\n", GT(pa), pa->philo_status[index_p_s].true_id, pa->odd);
			while (pa->philo_status[index_p_s].true_id != pa->odd)
						;
			printf("%ldm.s 		Repart odd avant adventage phil[%d]\n", GT(pa), pa->philo_status[index_p_s].true_id);
			// (printf("%ld philo[%d] wait BEFOR ADVANTAGE odd = %d\n", GT(pa), pa->philo_status[index_p_s].true_id, pa->odd));
		}
	}
	return (0);
}
int 	wait(t_para *pa, int index_p_s, int pass)
{
	pa->start_fonction++;
	while (pa->start_fonction < pa->nbr_philo)
		printf("%ldm.s waiting for all\n", GT(pa));
	if (pass == 0)
		return (1);
	if (pa->nbr_philo % 2 == 0)
	{
		
		if (pa->philo_status[index_p_s].true_id % 2 == 0)
		{
			printf("%ldm.s philo[%d] waiting wait in even\n", GT(pa), pa->philo_status[index_p_s].true_id);
			while (pa->odd != (pa->nbr_philo + 1))
				;
			pa->even = 2;
			printf("%ldm.s 	DEBLOK philo[%d] even\n", GT(pa), pa->philo_status[index_p_s].true_id);

		}
		else {
			if (pass == 1)
				return (1);
			printf("%ldm.s	ODD PHILO [%d] waiting wait in odd\n", GT(pa), pa->philo_status[index_p_s].true_id);
			while (pa->even != (pa->nbr_philo + 2))
				;
			pa->odd= 1;
			printf("%ldm.s 	DEBLOK philo[%d] odd\n", GT(pa), pa->philo_status[index_p_s].true_id);

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