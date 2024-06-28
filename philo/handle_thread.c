/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:52 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/27 18:08:13 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_philos(t_resource *resource)
{
	int	i;

	if (resource->num_philos == 1)
	{
		print_status(&resource->philos[0], FORK);
		usleep(resource->time_die * 1000);
		print_status(&resource->philos[0], DIE);
		check_finish(resource->philos, 1);
		pthread_join(resource->philos[0].thread, NULL);
		return (0);
	}
	i = 0;
	while (i < resource->num_philos)
	{
		if (pthread_create(&resource->philos[i].thread, NULL, \
				routine, &resource->philos[i]))
		{
			return (print_error(CREATE_ERR));
		}
		usleep(10);
		i++;
	}
	return (0);
}
