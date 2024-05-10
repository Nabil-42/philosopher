/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:40:06 by soelalou          #+#    #+#             */
/*   Updated: 2024/04/04 18:35:42 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_freetab_char(char **tab)
{
	size_t	i;
	
	if (tab == NULL)
        return;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_freetab_int(int **tab, size_t i)
{
	size_t	j;

	if (tab == NULL)
        return;
	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}
