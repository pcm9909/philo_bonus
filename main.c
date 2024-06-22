/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:17:07 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/22 20:25:25 by chunpark         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_resource	resource;

	if (argc == 5 || argc == 6)
	{
		validate_input(argv);
		preprocessing(argc, argv, &resource);
		fork_philos(&resource);
	}
	else
	{
		print_error(INPUT_ERR_3);
	}
	wait(NULL);
}
