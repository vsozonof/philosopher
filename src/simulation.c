/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:21:23 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/15 03:09:29 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
! ---------------------------------------------------------------------------
*							- ONE_PHILO_SOLUTION -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Simple solution for the one philo case,
* the philosopher will die after the given time because he can't eat :(

*/

int	one_philo_solution(t_data *ptr)
{
	ptr->start_time = ft_get_time();
	if (pthread_create(&ptr->tid[0], NULL, &one_philo_solver, &ptr->philos[0]))
		return (error_handler("Thread error.", ptr));
	if (pthread_join(ptr->tid[0], NULL))
		return (error_handler("Detach error.", ptr));
	end_prog_and_free(ptr);
	return (0);
}

void	*one_philo_solver(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + ft_get_time();
	event_log("has taken a fork", philo);
	ft_usleep(philo->data->death_time);
	event_log("died", philo);
	return (NULL);
}
/*
! ---------------------------------------------------------------------------
*							- MONITOR -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will simply monitor our philosopher and check if they ate
* the n-amount of time to end the simulation.
* - If a philo dies, it ends.


*/

void	*monitor(void *data_ptr)
{
	t_philo	*philo;
	int		ended;

	philo = (t_philo *) data_ptr;
	pthread_mutex_lock(&philo->data->lock);
	ended = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock);
	while (!ended)
	{
		pthread_mutex_lock(&philo->data->lock);
		ended = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->n_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (NULL);
}

/*
! ---------------------------------------------------------------------------
*							- ROUTINE -
! ---------------------------------------------------------------------------

? This function works as follows :
* - This is what our philo will be doing.
* - Will set the death timer.
* - Will make the philo eat, sleep and think.
* - Ends if a philo dies.

*/

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		ended;

	philo = (t_philo *) philo_pointer;
	pthread_mutex_lock(&philo->data->lock);
	ended = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock);
	philo->time_to_die = philo->data->death_time + ft_get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return (NULL);
	if (pthread_detach(philo->t1))
		return (NULL);
	while (!ended)
	{
		pthread_mutex_lock(&philo->data->lock);
		ended = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo);
		event_log("is thinking", philo);
	}
	return (NULL);
}

/*
! ---------------------------------------------------------------------------
*							- SUPERVISOR -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will simply handle the death of a philo and if he ate enough times
* - Will end the simulation depending on those situations.

*/

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;
	int		ended;

	philo = (t_philo *) philo_pointer;
	pthread_mutex_lock(&philo->data->lock);
	ended = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock);
	while (!ended)
	{
		pthread_mutex_lock(&philo->data->lock);
		ended = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
			event_log("died", philo);
		if (philo->eat_cont == philo->data->n_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}
