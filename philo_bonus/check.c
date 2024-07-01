/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:23:11 by chunpark          #+#    #+#             */
/*   Updated: 2024/07/01 13:58:24 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_finish(t_philo *philo, int status)
{
	sem_wait(philo->resource->cmp_finish);
	if (status == 2)
	{
		sem_post(philo->resource->cmp_finish);
		exit(0);
	}
	if (philo->resource->num_philos % 2 == 1)
	{
		if (status == 1 && philo->id == philo->resource->num_philos)
		{
			sem_post(philo->resource->cmp_finish);
			exit(0);
		}
		sem_post(philo->resource->cmp_finish);
	}
	else
	{
		if (status == 1 && philo->id == philo->resource->num_philos)
		{
			sem_post(philo->resource->cmp_finish);
			exit(0);
		}
		sem_post(philo->resource->cmp_finish);
	}
	return (0);
}

static void	sem_handler(int i, t_philo *philo)
{
	if (i == 0)
	{
		sem_wait(philo->resource->eat);
		sem_wait(philo->resource->time);
		sem_wait(philo->resource->count);
	}
	else if (i == 1)
	{
		sem_post(philo->resource->count);
		sem_post(philo->resource->time);
		sem_post(philo->resource->eat);
	}
}

static int	check_dead(t_philo *philo)
{
	sem_handler(0, philo);
	if (get_time() - philo->time_last_eat > philo->resource->time_die)
	{
		print_status(philo, DIE);
		check_finish(philo, 2);
		sem_handler(1, philo);
		return (1);
	}
	else if (philo->resource->cnt_must_eat != -1 \
				&& philo->cnt_eat >= philo->resource->cnt_must_eat)
	{
		check_finish(philo, 1);
		sem_handler(1, philo);
	}
	else
	{
		sem_handler(1, philo);
	}
	return (0);
}

void	*checker(void *philos)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)philos;
	status = 1;
	while (status)
	{
		if (check_dead(philo))
		{
			status = 0;
		}
	}
	pthread_join(philo->checker, NULL);
	return (NULL);
}
