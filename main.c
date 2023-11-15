/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 06:58:39 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/15 03:45:55 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
! ---------------------------------------------------------------------------
*							- INIT_MASTER -
! ---------------------------------------------------------------------------

? This function will call multiple functions as follows :
* - init_struct : will initialize the structure variables.
* - init_forks  : will initialize the mutexes.
* - init_philos : will initialize the variables of the
* philo structures.
* - init_thread : will create the needed threads.

! - The function will also check if there is only one
! philosopher, and will just call the one_philo_solution to solve
! the problem.

*/

int	init_master(t_data *ptr, char **argv)
{
	init_struct(ptr, argv);
	if (init_pointers(ptr))
		return (0);
	init_forks(ptr);
	init_philos(ptr);
	if (ptr->n_philo == 1)
		return (one_philo_solution(ptr));
	if (init_threads(ptr))
		return (0);
	return (1);
}

/*
! ---------------------------------------------------------------------------
*							- MAIN -
! ---------------------------------------------------------------------------

? The main function works as follows :
* - Check if enough arguments are given.
* - Check if the arguments are valid.
* - Allocate the memory for our data structure
* - Free in case of error (we are never too sure :3)

*/

int	main(int argc, char **argv)
{
	t_data			*ptr;

	if (argc < 5 || argc > 6)
		return (pr_error("Not enough arguments."));
	if (!verify_arguments(argv, argc))
		return (0);
	ptr = malloc(sizeof(t_data));
	if (!ptr)
		return (0);
	if (!init_master(ptr, argv))
		return (0);
	end_prog_and_free(ptr);
	return (1);
}
