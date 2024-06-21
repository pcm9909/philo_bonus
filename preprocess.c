/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:15:13 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/20 03:25:09 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_resource(char **argv, int argc, t_resource *resource)
{
	resource->num_philos = ft_atoi(argv[1]);
	resource->time_die = ft_atoi(argv[2]);
	resource->time_eat = ft_atoi(argv[3]);
	resource->time_sleep = ft_atoi(argv[4]);
	resource->time_stamp = get_time();
	resource->finish = 0;
	if (resource->time_stamp == 1)
	{
		print_error(TIME_ERR);
	}
	if (argc == 6)
	{
		resource->cnt_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		resource->cnt_must_eat = -1;
	}
}

static void	alloc_resource(t_resource *resource)
{
	int	num_of_philos;
	int	i;

	num_of_philos = resource->num_philos;
	resource->philos = malloc(sizeof(t_philo) * num_of_philos);
	if (!resource->philos)
		print_error(ALLOC_ERR);
	resource->time_stamp = get_time();
	i = 0;
	while (i < num_of_philos)
	{
		resource->philos[i].id = i + 1;
		resource->philos[i].cnt_eat = 0;
		resource->philos[i].time_last_eat = resource->time_stamp;
		resource->philos[i].resource = resource;
		i++;
	}
}

static sem_t	*init_sem(char *name, int count)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0644, count);
	if (errno == SEM_FAILED)
	{
		print_error(SEM_OPEN_ERR);
	}
	return sem;
}

static void	open_sem(t_resource *resource)
{
	resource->write = init_sem("/write", 1);
	resource->forks = init_sem("/forks", resource->num_philos);
	resource->eat = init_sem("/eat", 1);
	resource->cmp_finish = init_sem("/cmp_finish", 1);
}

void	preprocessing(int argc, char **argv, t_resource *resource)
{
	init_resource(argv, argc, resource);
	alloc_resource(resource);
	open_sem(resource);
}