#include "philo.h"

void	ft_take_fork(int side, t_philo *philo)
{
	int				*state;
	pthread_mutex_t	*fork;

	if (side == LEFT)
	{
		state = &philo->lf_state;
		fork = philo->lf_mutex;
	}
	else if (side == RIGHT)
	{
		state = &philo->rf_state;
		fork = philo->rf_mutex;
	}
	if (ft_necrology(philo))
		return ;
	if (*state == DOWN)
	{
		pthread_mutex_lock(fork);
		*state = UP;
		pthread_mutex_lock(&philo->args->print_mutex);
		if (!ft_necrology(philo))
			printf("⏰ %ld - 🧙(%d) has taken a fork 🥄\n",
				ft_timestamp(), philo->id);
		pthread_mutex_unlock(&philo->args->print_mutex);
	}
}

void	*ft_philosophe(void *input)
{
	t_philo		*philo;

	philo = (t_philo *)input;
	if (philo->id % 2)
		usleep(60000);
	while (!ft_necrology(philo) && philo->loop != philo->args->n_loop)
	{
		ft_take_fork(LEFT, philo);
		if (philo->lf_state == UP && philo->args->n_philo > 1)
			ft_take_fork(RIGHT, philo);
		if (philo->lf_state == UP && philo->rf_state == UP)
		{
			ft_status(EAT, philo, philo->args);
			(pthread_mutex_unlock(philo->rf_mutex), philo->rf_state = DOWN);
			(pthread_mutex_unlock(philo->lf_mutex), philo->lf_state = DOWN);
			ft_status(SLEEP, philo, philo->args);
			ft_status(THINK, philo, philo->args);
		}
	}
	if (philo->rf_state == UP)
		pthread_mutex_unlock(philo->rf_mutex);
	if (philo->lf_state == UP)
		pthread_mutex_unlock(philo->lf_mutex);
	return (NULL);
}

void	*ft_supervise(void *input)
{
	t_philo	*philo;
	t_philo	*tmp;
	t_args	*args;

	philo = (t_philo *)input;
	args = philo->args;
	tmp = philo;
	while (tmp)
	{
		pthread_mutex_lock(&(args->philo_mutex));
		if (tmp->loop == args->n_loop)
			return (pthread_mutex_unlock(&(args->philo_mutex)), NULL);
		if (ft_timestamp() - tmp->lst_meal > args->tt_die / 1000)
		{
			pthread_mutex_unlock(&(args->philo_mutex));
			return (ft_status(DIE, tmp, args), NULL);
		}
		pthread_mutex_unlock(&(args->philo_mutex));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_philosophers(t_philo *philos)
{
	t_philo	*tmp;
	int		i;

	tmp = philos;
	i = -1;
	while (++i < philos->args->n_philo)
	{
		if (pthread_create(&tmp->th_philo, NULL, ft_philosophe, tmp))
			return (ft_print_error("A philosopher thread creation failed"));
		tmp = tmp->next;
	}
	if (pthread_create(&(philos->args->th_supervisor), NULL, ft_supervise,
			philos))
		return (ft_print_error("The supervisor thread creation failed"));
	tmp = philos;
	i = -1;
	while (++i < philos->args->n_philo)
	{
		if (pthread_join(tmp->th_philo, NULL))
			return (ft_print_error("A philosopher thread join failed"));
		tmp = tmp->next;
	}
	if (pthread_join(philos->args->th_supervisor, NULL))
		return (ft_print_error("The supervisor thread join failed"));
	return (EXIT_SUCCESS);
}
