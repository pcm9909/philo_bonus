/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:15:18 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/14 16:39:00 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *str)
{
	if (check_finish(philo, 0))
		return ;
	pthread_mutex_lock(&philo->resource->mutex_print);
	ft_putnbr_fd(get_time() - philo->resource->time_stamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&philo->resource->mutex_print);
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}
