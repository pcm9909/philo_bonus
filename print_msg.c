/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:15:18 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/21 02:50:29 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *str)
{
	check_finish(philo, 0);
	sem_wait(philo->resource->write);
	ft_putnbr_fd(get_time() - philo->resource->time_stamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
	sem_post(philo->resource->write);
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit (1);
}
