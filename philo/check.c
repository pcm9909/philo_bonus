/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:38 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/14 20:55:26 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_finish(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->resource->mutex_cmp_finish);
	if (status)
	{
		philo->resource->finish = 1;
	}
	if (philo->resource->finish)
	{
		pthread_mutex_unlock(&philo->resource->mutex_cmp_finish);
		return (1);
	}
	pthread_mutex_unlock(&philo->resource->mutex_cmp_finish);
	return (0);
}

static int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->resource->mutex_eat);
	if (get_time() - philo->time_last_eat >= philo->resource->time_die)
	{
		print_status(philo, DIE);
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->resource->mutex_eat);
		return (1);
	}
	else if (philo->resource->cnt_must_eat != -1 \
				&& philo->cnt_eat >= philo->resource->cnt_must_eat)
	{
		philo->resource->cmp_finish_eat++;
		if (philo->resource->cmp_finish_eat >= philo->resource->num_philos)
		{
			check_finish(philo, 1);
			pthread_mutex_unlock(&philo->resource->mutex_eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->resource->mutex_eat);
	return (0);
}

int	checker(t_resource *resource)
{
	int	i;
	int	status;

	status = 1;
	while (status)
	{
		i = -1;
		resource->cmp_finish_eat = 0;
		while (++i < resource->num_philos)
		{
			if (check_dead(&resource->philos[i]))
			{
				status = 0;
			}
		}
	}
	i = -1;
	while (++i < resource->num_philos)
	{
		pthread_join(resource->philos[i].thread, NULL);
	}
	return (free_resource(resource));
}
