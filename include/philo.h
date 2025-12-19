#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_var t_var;
typedef pthread_mutex_t t_fork;

typedef struct	s_philo
{
	int			id;
	pthread_t	th_id;
	bool		full;
	long long	last_meal;
	t_fork		*left;
	t_fork		*right;
	t_var		*var;
}				t_philo;

struct	s_var
{
	int			nbr_ph;
	long long	tm_die;
	long long	tm_eat;
	long long	tm_sleep;
	int			must_eat;
	long long	start_tm;
	bool		start;
	pthread_t	*threads;
	pthread_t	check_die;
	t_philo		*philos;
	t_fork		*forks;
	t_fork		start_mutex;
};
// ======= free and exit funcs	=============
void	ft_cleanup(t_var *var, int fork_i, int th_i);
void	ft_failure_exit(char *mes, t_var *var, int fork_i, int th_i);

// ======= initialization funcs =============
void	init_var(int ac, char **av, t_var *var);
void	create_philos_threads(t_var *var);

// ======= routines funcs ====================
void	*check_routine(void *arg);
void	*routine(void *arg);

#endif