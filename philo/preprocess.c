/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:15:13 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/14 16:43:43 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_resource(char **argv, int argc, t_resource *resource)
{
	resource->num_philos = ft_atoi(argv[1]);
	resource->time_die = ft_atoi(argv[2]);
	resource->time_eat = ft_atoi(argv[3]);
	resource->time_sleep = ft_atoi(argv[4]);
	resource->time_stamp = get_time();
	resource->finish = 0;
	if (resource->time_stamp == 1)
	{
		return (print_error(TIME_ERR));
	}
	if (argc == 6)
	{
		resource->cnt_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		resource->cnt_must_eat = -1;
	}
	return (0);
}

static int	alloc_resource(t_resource *resource)
{
	int	num_of_philos;
	int	i;

	num_of_philos = resource->num_philos;
	resource->philos = malloc(sizeof(t_philo) * num_of_philos);
	if (!resource->philos)
		return (print_error(ALLOC_ERR));
	resource->forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if (!resource->forks)
		return (print_error(ALLOC_ERR));
	resource->time_stamp = get_time();
	i = 0;
	while (i < num_of_philos)
	{
		resource->philos[i].id = i + 1;
		resource->philos[i].cnt_eat = 0;
		resource->philos[i].l_fork = i;
		resource->philos[i].r_fork = (i + 1) % num_of_philos;
		resource->philos[i].cnt_eat = 0;
		resource->philos[i].time_last_eat = resource->time_stamp;
		resource->philos[i].resource = resource;
		i++;
	}
	return (0);
}

static int	init_mutex(t_resource *resource)
{
	int	i;

	i = 0;
	while (i < resource->num_philos)
	{
		if (pthread_mutex_init(&resource->forks[i], NULL))
		{
			return (print_error(MUTEX_ERR_1));
		}
		i++;
	}
	if (pthread_mutex_init(&resource->mutex_print, NULL))
	{
		return (print_error(MUTEX_ERR_1));
	}
	if (pthread_mutex_init(&resource->mutex_eat, NULL))
	{
		return (print_error(MUTEX_ERR_1));
	}
	if (pthread_mutex_init(&resource->mutex_cmp_finish, NULL))
	{
		return (print_error(MUTEX_ERR_1));
	}
	return (0);
}

int	preprocessing(int argc, char **argv, t_resource *resource)
{
	if (init_resource(argv, argc, resource))
	{
		return (1);
	}
	if (alloc_resource(resource))
	{
		return (1);
	}
	if (init_mutex(resource))
	{
		return (1);
	}
	return (0);
}
