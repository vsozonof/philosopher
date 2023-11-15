/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:49:41 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/04 18:02:43 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	ft_get_time(void)
{
	struct timeval	value;

	if (gettimeofday(&value, NULL))
		return (error_handler("gettimeofday() error", NULL));
	return ((value.tv_sec * (u_int64_t)1000) + (value.tv_usec / 1000));
}
