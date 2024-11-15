#include "philo.h"

void	*ft_think(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->print_mutex);
	if (!ft_necrology(philo))
		printf("⏰ %ld - 🧙(%d) is thinking 🤔\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&args->print_mutex);
	return (NULL);
}

void	*ft_eat(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->print_mutex);
	if (!ft_necrology(philo))
		printf("⏰ %ld - 🧙(%d) is eating 😋 for the %d times\n",
			ft_timestamp(), philo->id, philo->loop + 1);
	pthread_mutex_unlock(&args->print_mutex);
	pthread_mutex_lock(&args->philo_mutex);
	philo->lst_meal = ft_timestamp();
	pthread_mutex_unlock(&args->philo_mutex);
	usleep(args->tt_eat);
	pthread_mutex_lock(&args->philo_mutex);
	philo->loop++;
	pthread_mutex_unlock(&args->philo_mutex);
	return (NULL);
}

void	*ft_sleep(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->print_mutex);
	if (!ft_necrology(philo))
		printf("⏰ %ld - 🧙(%d) is sleeping 😴\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&args->print_mutex);
	usleep(args->tt_sleep);
	return (NULL);
}

void	*ft_die(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->death_mutex);
	args->b_dead = 1;
	pthread_mutex_unlock(&args->death_mutex);
	pthread_mutex_lock(&args->print_mutex);
	printf("⏰ %ld - 🧙(%d) died 😵\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&args->print_mutex);
	return (NULL);
}

void	*ft_status(char state, t_philo *philo, t_args *args)
{
	if (state == THINK)
		return (ft_think(philo, args));
	else if (state == EAT)
		return (ft_eat(philo, args));
	else if (state == SLEEP)
		return (ft_sleep(philo, args));
	else if (state == DIE)
		return (ft_die(philo, args));
	return (NULL);
}
