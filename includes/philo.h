/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 06:58:53 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/15 03:58:42 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>

// ! ---------------------------------------------------------------------------
// ?							STRUCTURES DECLARATION
// ! ---------------------------------------------------------------------------

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				n_philo;
	int				n_meals;
	int				dead;
	int				finished;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	end;
	pthread_t		*tid;
}	t_data;

// ! ---------------------------------------------------------------------------
// *							-  UTILS -
// ! ---------------------------------------------------------------------------

long		ft_atol(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_int_overflow_checker(char *str);
int			ft_integer_checker(char *str);
int			ft_usleep(useconds_t time);
int			pr_error(char *error);
size_t		ft_strlen(const char *str);
u_int64_t	ft_get_time(void);

// ! ---------------------------------------------------------------------------
// *						- ARGUMENTS VERIFICATION -
// ! ---------------------------------------------------------------------------

int			verify_arguments(char **argv, int argc);
int			prevent_overflow(char **argv, int argc);

// ! ---------------------------------------------------------------------------
// *							- INITIALIZERS -
// ! ---------------------------------------------------------------------------

int			init_master(t_data *ptr, char **argv);
int			init_pointers(t_data *ptr);
void		init_struct(t_data *ptr, char **argv);
void		init_philos(t_data *ptr);
void		init_forks(t_data *ptr);
int			init_threads(t_data *ptr);

// ! ---------------------------------------------------------------------------
// *						- PHILOSOPHERS SIMULATION -
// ! ---------------------------------------------------------------------------

int			one_philo_solution(t_data *ptr);
void		*one_philo_solver(void *philo_ptr);
void		*routine(void *philo_pointer);
void		*monitor(void *data_ptr);
void		*supervisor(void *philo_pointer);
void		event_log(char *str, t_philo *philo);
void		eat(t_philo *philo);
void		take_forks_r_l(t_philo *philo);
void		take_forks_l_r(t_philo *philo);
void		drop_forks_l_r(t_philo *philo);
void		drop_forks_r_l(t_philo *philo);

// ! ---------------------------------------------------------------------------
// *					- FREE FUNCTIONS && ERROR HANDLING -
// ! ---------------------------------------------------------------------------

int			error_handler(char *str, t_data *ptr);
void		end_prog_and_free(t_data *ptr);
void		free_data(t_data *ptr);

#endif