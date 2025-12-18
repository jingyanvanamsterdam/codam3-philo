#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_var t_var;

typedef struct s_fork
{
	pthread_mutex_t	*fork;
	int				id;
}				t_fork;

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
	int			nbr_philos;
	long long	tm_die;
	long long	tm_eat;
	long long	tm_sleep;
	int			must_eat;
	pthread_t	*threads;
};

#endif