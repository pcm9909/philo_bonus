/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:17:07 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/28 18:25:59 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_resource	resource;
	int			status;
	int			i;

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
	wait(&status);
	i = 0;
	while (i < resource.num_philos)
	{
		kill(resource.philos[i].pid, SIGKILL);
		i++;
	}
	free_resource(&resource);
}
