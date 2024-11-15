#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define LEFT			1
# define RIGHT			-1
# define UP				1
# define DOWN			0
# define RED 			"\033[0;31m"
# define GREEN 			"\033[0;32m"
# define YELLOW 		"\033[0;33m"
# define BLUE 			"\033[0;34m"
# define MAGENTA 		"\033[0;35m"
# define CYAN 			"\033[0;36m"
# define RESET_COLOR 	"\033[0m"
# define INT_MAX		2147483647

typedef enum s_action
{
	THINK = 0,
	EAT,
	SLEEP,
	DIE
}	t_action;

typedef struct s_args
{
	int				n_philo;
	int				n_loop;
	int				b_dead;
	int				b_mutex;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	pthread_t		th_supervisor;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	philo_mutex;
}	t_args;

typedef struct s_philo
{
	t_args			*args;
	int				id;
	int				loop;
	int				rf_state;
	int				lf_state;
	int				b_mutex;
	time_t			lst_meal;
	pthread_t		th_philo;
	pthread_mutex_t	*rf_mutex;
	pthread_mutex_t	*lf_mutex;
	struct s_philo	*next;
	struct s_philo	*previous;
}	t_philo;

int		ft_error(char *message, t_args *args, t_philo *philos);
t_philo	*ft_lstlast(t_philo *lst);
int		ft_necrology(t_philo *philo);
int		ft_philosophers(t_philo *philos);
int		ft_print_error(char *message);
time_t	ft_timestamp(void);
void	*ft_status(char state, t_philo *philo, t_args *args);
// void	ft_print_args(t_args *args);
// void	ft_print_philo(t_philo *philo);

#endif