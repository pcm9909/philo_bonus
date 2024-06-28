/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:26:33 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/28 18:29:39 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_resource(t_resource *resource)
{
	free(resource->philos);
	sem_close(resource->eat);
	sem_close(resource->write);
	sem_close(resource->forks);
	sem_close(resource->cmp_finish);
}

void	free_and_exit_process(t_philo *philo)
{
	free_resource(philo->resource);
	exit(0);
}
