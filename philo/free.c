/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:47 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/14 16:33:17 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	free_resource(t_resource *resource)
{
	int	i;

	i = 0;
	while (i < resource->num_philos)
	{
		pthread_mutex_destroy(&resource->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&resource->mutex_print);
	pthread_mutex_destroy(&resource->mutex_eat);
	pthread_mutex_destroy(&resource->mutex_cmp_finish);
	free(resource->philos);
	free(resource->forks);
	return (0);
}
