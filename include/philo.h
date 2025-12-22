#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef enum	e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRSt_mutex,
	TAKE_SECOND_FORK,
	DIED
}				t_status;

typedef struct s_var t_var;
typedef pthread_mutex_t t_mutex;

typedef struct	s_philo
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
	bool		start; //when everyone eat == must_eat; or someone died.

	t_mutex		write_mutex;
};

// Utils: getter and setter with mutex lock and unlock
bool	get_bool(t_mutex *mutex, bool *value);
void	set_bool(t_mutex *mutex, bool *dest, bool value);

long long	get_ms_time(void);

// ======= locks 				============
void	get_start(t_var *var);
void	console_status(t_philo *philo, t_status status);
void	eating(t_philo *philo);
void	sleep_think(t_philo *philo);

// ======= free and exit funcs	=============
void	ft_cleanup(t_var *var, int fork_i, int th_i);
void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i);

// ======= initialization funcs =============
void	init_var(int ac, char **av, t_var *var);
void	create_philos_threads(t_var *var);

// ======= routines funcs ====================
void	*check_death(void *arg);
void	*routine(void *arg);

#endif