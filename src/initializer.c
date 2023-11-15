/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:22:55 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/15 03:52:48 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
! ---------------------------------------------------------------------------
*							- INIT_THREADS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will set up the starting time.
* - Will create a monitoring thread if a required n of meal
* is specified.
* - Will create a thread for each philosopher and set a routine for
* all of them.
* - Will use pthread_join to synchronize the execution of the routine.

*/

int	init_threads(t_data *ptr)
{
	int			i;
	pthread_t	t0;

	i = -1;
	ptr->start_time = ft_get_time();
	if (ptr->n_meals > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &ptr->philos[0]))
			return (error_handler("Thread creation error.", ptr));
		if (pthread_detach(t0))
			return (error_handler("Detach error.", ptr));
	}
	while (++i < ptr->n_philo)
	{
		if (pthread_create(&ptr->tid[i], NULL, &routine, &ptr->philos[i]))
			return (error_handler("Thread creation error.", ptr));
		ft_usleep(1);
	}
	i = -1;
	while (++i < ptr->n_philo)
	{
		if (pthread_join(ptr->tid[i], NULL))
			return (error_handler("Thread join error.", ptr));
	}
	return (0);
}

/*
! ---------------------------------------------------------------------------
*							- INIT_PHILOS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will initialize the variables of the philo struct
* and this, for each philosopher existing.

*/

void	init_philos(t_data *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->n_philo)
	{
		ptr->philos[i].data = ptr;
		ptr->philos[i].id = i + 1;
		ptr->philos[i].time_to_die = ptr->death_time;
		ptr->philos[i].eat_cont = 0;
		ptr->philos[i].eating = 0;
		ptr->philos[i].status = 0;
		pthread_mutex_init(&ptr->philos[i].lock, NULL);
		i++;
	}
}

/*
! ---------------------------------------------------------------------------
*							- INIT_STRUCT -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will initialize the variables of the data structure.
* - Will initialize the mutexes.

*/

void	init_struct(t_data *ptr, char **argv)
{
	ptr->n_philo = ft_atol(argv[1]);
	ptr->death_time = (u_int16_t) ft_atol(argv[2]);
	ptr->eat_time = (u_int16_t) ft_atol(argv[3]);
	ptr->sleep_time = (u_int16_t) ft_atol(argv[4]);
	if (argv[5])
		ptr->n_meals = ft_atol(argv[5]);
	else
		ptr->n_meals = 0;
	ptr->dead = 0;
	ptr->finished = 0;
	pthread_mutex_init(&ptr->write, NULL);
	pthread_mutex_init(&ptr->lock, NULL);
	pthread_mutex_init(&ptr->end, NULL);
}

/*
! ---------------------------------------------------------------------------
*							- INIT_POINTERS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will allocate the memory for our variables.

*/

int	init_pointers(t_data *ptr)
{
	ptr->tid = malloc(sizeof(pthread_t) * ptr->n_philo);
	if (!ptr->tid)
		return (error_handler("Allocation error.", ptr));
	ptr->forks = malloc(sizeof(pthread_mutex_t) * ptr->n_philo);
	if (!ptr->forks)
		return (error_handler("Allocation error.", ptr));
	ptr->philos = malloc(sizeof(t_philo) * ptr->n_philo);
	if (!ptr->philos)
		return (error_handler("Allocation error.", ptr));
	return (0);
}

/*
! ---------------------------------------------------------------------------
*							- INIT_FORKS -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will initialize all the forks (1 fork / philo).
* - Will set a left fork and a right fork to each philo.

*/

void	init_forks(t_data *ptr)
{
	int	i;

	i = -1;
	while (++i < ptr->n_philo)
		pthread_mutex_init(&ptr->forks[i], NULL);
	i = 0;
	ptr->philos[0].l_fork = &ptr->forks[0];
	ptr->philos[0].r_fork = &ptr->forks[ptr->n_philo - 1];
	i = 1;
	while (i < ptr->n_philo)
	{
		ptr->philos[i].l_fork = &ptr->forks[i];
		ptr->philos[i].r_fork = &ptr->forks[i - 1];
		i++;
	}
}
