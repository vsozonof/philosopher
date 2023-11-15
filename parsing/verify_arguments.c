/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:12:12 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/02 16:21:20 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_arguments(char **argv, int argc)
{
	if (!prevent_overflow(argv, argc))
		return (0);
	else if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (pr_error("Invalid amount of philosophers."));
	else if (ft_atol(argv[2]) <= 0 || ft_atol(argv[3]) <= 0
		|| ft_atol(argv[4]) <= 0 || (argv[5] && ft_atol(argv[5]) <= 0))
		return (pr_error("Invalid value detected."));
	return (1);
}

int	prevent_overflow(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_int_overflow_checker(argv[i]))
			return (0);
		else
			i++;
	}
	return (1);
}
