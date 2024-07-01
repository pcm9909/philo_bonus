/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:18:47 by chunpark          #+#    #+#             */
/*   Updated: 2024/07/01 13:33:22 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->resource->forks);
	print_status(philo, FORK);
	sem_wait(philo->resource->forks);
	print_status(philo, FORK);
}

static void	ft_drop_forks(t_philo *philo)
{
	sem_post(philo->resource->forks);
	sem_post(philo->resource->forks);
}

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->resource->eat);
	print_status(philo, EAT);
	sem_wait(philo->resource->time);
	philo->time_last_eat = get_time();
	sem_post(philo->resource->time);
	usleep(philo->resource->time_eat * 1000);
	sem_wait(philo->resource->count);
	philo->cnt_eat++;
	sem_post(philo->resource->count);
	sem_post(philo->resource->eat);
}

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->resource->time_sleep * 1000);
	if (philo->resource->num_philos % 2 == 1 && philo->id % 2 == 1)
		usleep(philo->resource->time_eat + 500);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->checker, NULL, checker, philo);
	if (philo->resource->num_philos % 2 == 1 && philo->id % 2 == 1)
	{
		usleep(philo->resource->time_eat * 1000);
	}
	if (philo->resource->num_philos % 2 == 0 && philo->id % 2 == 0)
	{
		usleep(philo->resource->time_eat * 1000);
	}
	while (1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_drop_forks(philo);
		ft_sleep(philo);
		print_status(philo, THINK);
	}
}
