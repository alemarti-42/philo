/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:35:45 by alemarti          #+#    #+#             */
/*   Updated: 2022/09/22 17:52:05 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO: philo_start
void	philo_start(t_philo *philos)
{

}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	//philos = malloc(1);
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Wrong number of arguments", NULL));
	if (init_philos(&philos, argc, argv))
		return (ft_error("Error: Failed to initialize philos", NULL));
	//philo_start(philos);
	return (0);
}