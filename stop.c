/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:27:28 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/19 18:28:17 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	trigger_stop(t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	data->flag_stop = 1;
	pthread_mutex_unlock(&data->mutex_data);
}

int	check_stop(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_data);
	res = data->flag_stop;
	pthread_mutex_unlock(&data->mutex_data);
	return (res);
}
