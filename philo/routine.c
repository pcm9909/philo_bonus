/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:15:00 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/27 16:52:57 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->resource->forks[philo->l_fork]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->resource->forks[philo->r_fork]);
	print_status(philo, FORK);
}

static void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->resource->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->resource->forks[philo->r_fork]);
}

static void	ft_eat(t_philo *philo)
{
	print_status(philo, EAT);
	philo->time_last_eat = get_time();
	usleep(philo->resource->time_eat * 1000);
	pthread_mutex_lock(&philo->resource->mutex_eat);
	philo->cnt_eat++;
	pthread_mutex_unlock(&philo->resource->mutex_eat);
}

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->resource->time_sleep * 1000);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	print_status(philo, THINK);
	if (philo->id % 2 == 0)
	{
		usleep(philo->resource->time_eat * 1000);
	}
	while (1)
	{
		if (check_finish(philo, 0))
			return (0);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_drop_forks(philo);
		ft_sleep(philo);
		print_status(philo, THINK);
	}
}
