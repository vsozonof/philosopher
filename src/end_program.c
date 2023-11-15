/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:15 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/14 23:33:24 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
! ---------------------------------------------------------------------------
*							- ERROR_HANDLER -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will print the error.
* - Will quit the program properly if the memory isn't freed.

*/

int	error_handler(char *str, t_data *ptr)
{
	pr_error(str);
	if (ptr)
		end_prog_and_free(ptr);
	return (1);
}

/*
! ---------------------------------------------------------------------------
*							- END_PROG_AND_FREE -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Will free by the use of the destroy functions
*   all the created mutexes.
* - Will call free_data to free the remaining variables.

*/

void	end_prog_and_free(t_data *ptr)
{
	int	i;

	i = -1;
	while (++i < ptr->n_philo)
	{
		pthread_mutex_destroy(&ptr->forks[i]);
		pthread_mutex_destroy(&ptr->philos[i].lock);
	}
	pthread_mutex_destroy(&ptr->write);
	pthread_mutex_destroy(&ptr->lock);
	free_data(ptr);
}

/*
! ---------------------------------------------------------------------------
*							- FREE_DATA -
! ---------------------------------------------------------------------------

? This function works as follows :
* - Frees variable if non-null.

*/

void	free_data(t_data *ptr)
{
	if (ptr->tid)
		free(ptr->tid);
	if (ptr->forks)
		free(ptr->forks);
	if (ptr->philos)
		free(ptr->philos);
	if (ptr)
		free(ptr);
}
