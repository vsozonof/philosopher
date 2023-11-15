/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_writer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:38:41 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/27 07:51:50 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pr_error(char *error)
{
	printf("\033[1;31m");
	printf("Error: %s\n", error);
	printf("\033[0;37m");
	return (0);
}
