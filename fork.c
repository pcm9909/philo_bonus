/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:19:42 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/22 19:40:11 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_philos(t_resource *resource)
{
	int	i;

	i = 0;
	if (resource->num_philos == 1)
	{
		print_status(resource->philos, FORK);
		usleep(resource->time_die * 1000);
		print_status(resource->philos, DIE);
		exit(1);
	}
	while (i < resource->num_philos)
	{
		resource->philos[i].pid = fork();
		if (resource->philos[i].pid == 0)
		{
			routine(&resource->philos[i]);
		}
		else if (resource->philos[i].pid < 0)
		{
			print_error(FORK_ERR);
		}
		usleep(200);
		i++;
	}
}
