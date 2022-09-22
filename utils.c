/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:37:31 by alemarti          #+#    #+#             */
/*   Updated: 2022/09/22 17:21:24 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	//if (data->mutex_printf != 0)
		pthread_mutex_destroy(&data->mutex_printf);
	//if (data->mutex_fork == 0)
		pthread_mutex_destroy(data->mutex_fork);
	free (data);
}

int	ft_error(char *str, void *ptr)
{
	int	i;

	i = 0;
	if (ptr)
		free (ptr);
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	return (-1);
}