/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:33:05 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/15 04:11:50 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
! ---------------------------------------------------------------------------
*							- TAKE_FORKS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will lock the left and right fork using the mutexes as needed.
* - Will print the event message.
! - The only difference is the picking order.

*/

void	take_forks_r_l(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	event_log("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	event_log("has taken a fork", philo);
}

void	take_forks_l_r(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	event_log("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	event_log("has taken a fork", philo);
}

/*
! ---------------------------------------------------------------------------
*							- DROP_FORKS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will unlock the left and right fork using the mutexes as needed.
* - Will print the event message.
! - The only difference is the dropping order.

*/

void	drop_forks_l_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	event_log("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
}

void	drop_forks_r_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	event_log("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
}
