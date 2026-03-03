/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 14:58:12 by jdong         #+#    #+#                 */
/*   Updated: 2026/01/22 17:58:52 by jdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	FULL
}			t_status;

typedef struct s_var	t_var;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int			id;
	pthread_t	th_id;
	bool		full;
	long long	last_meal;
	int			meals;
	t_mutex		*first;
	t_mutex		*second;
	t_mutex		meal_mut;
	t_var		*var;
}				t_philo;

struct	s_var
{
	int			nbr_ph;
	long long	tm_die;
	long long	tm_eat;
	long long	tm_sleep;
	int			must_eat;

	pthread_t	*threads;
	pthread_t	check_die;

	t_philo		*philos;
	t_mutex		*forks;

	t_mutex		start_mutex;
	long long	start_tm;
	bool		start;

	t_mutex		write_mutex;
	t_mutex		stop_mutex;
	bool		stop;
};

// Utils: getter and setter with mutex lock and unlock
bool		get_bool(t_mutex *mutex, bool *value);
void		set_bool(t_mutex *mutex, bool *dest, bool value);

long long	get_us_time(void);
void		get_start(t_var *var);
void		console_status(t_philo *philo, t_status status);

// ======= free and exit funcs	=============
void		ft_cleanup(t_var *var, int fork_i, int th_i);
void		ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i);

// ======= initialization funcs =============
void		init_var(int ac, char **av, t_var *var);
void		create_philos_threads(t_var *var);

// ======= routines funcs ====================
void		*check_death(void *arg);
void		eating(t_philo *philo);
void		sleep_think(t_philo *philo);
void		*routine(void *arg);

#endif