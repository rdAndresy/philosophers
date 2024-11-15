#include "philo.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

time_t	ft_timestamp(void)
{
	static struct timeval	start;
	struct timeval			current;

	if (start.tv_sec == 0 && start.tv_usec == 0)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	else
		gettimeofday(&current, NULL);
	return ((current.tv_sec - start.tv_sec) * 1000
		+ (current.tv_usec - start.tv_usec) / 1000);
}

int	ft_necrology(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&(philo->args->death_mutex));
	state = philo->args->b_dead;
	pthread_mutex_unlock(&(philo->args->death_mutex));
	return (state);
}

int	ft_print_error(char *message)
{
	int	i;

	if (!message)
		return (EXIT_FAILURE);
	i = 0;
	write(2, RED, 8);
	while (message[i])
		write(2, &message[i++], 1);
	write(2, RESET_COLOR, 5);
	return (EXIT_FAILURE);
}

int	ft_error(char *message, t_args *args, t_philo *philos)
{
	t_philo	*tmp;

	(ft_print_error(message), tmp = philos);
	if (philos)
	{
		while (args->n_philo > 0)
		{
			if (philos->b_mutex)
				(pthread_mutex_destroy(philos->lf_mutex),
					free(philos->lf_mutex));
			philos = tmp->next;
			(free(tmp), tmp = philos, args->n_philo--);
		}
	}
	if (args)
		if (args && args->b_mutex)
			(pthread_mutex_destroy(&args->philo_mutex),
				pthread_mutex_destroy(&args->print_mutex),
				pthread_mutex_destroy(&args->philo_mutex));
	if (args)
		free(args);
	return (EXIT_FAILURE);
}

// void	ft_print_args(t_args *args)
// {
// 	printf(BLUE "######## ARGUMENTS ########" RESET_COLOR "\n");
// 	printf(CYAN "n_philo: " RESET_COLOR "%d\n", args->n_philo);
// 	printf(CYAN "n_loop: " RESET_COLOR "%d\n", args->n_loop);
// 	printf(CYAN "b_dead: " RESET_COLOR "%d\n", args->b_dead);
// 	printf(CYAN "b_mutex: " RESET_COLOR "%d\n", args->b_mutex);
// 	printf(CYAN "tt_die: " RESET_COLOR "%ld\n", args->tt_die / 1000);
// 	printf(CYAN "tt_eat: " RESET_COLOR "%ld\n", args->tt_eat / 1000);
// 	printf(CYAN "tt_slp: " RESET_COLOR "%ld\n", args->tt_sleep / 1000);
// 	printf("\n");
// }

// void	ft_print_philo(t_philo *philo)
// {
// 	printf(BLUE "######## FIRST PHILO ########" RESET_COLOR "\n");
// 	printf(CYAN "id: " RESET_COLOR "%d\n", philo->id);
// 	printf(CYAN "loop: " RESET_COLOR "%d\n", philo->loop);
// 	printf(CYAN "rf_state: " RESET_COLOR "%d\n", philo->rf_state);
// 	printf(CYAN "lf_state: " RESET_COLOR "%d\n", philo->lf_state);
// 	printf(CYAN "b_mutex: " RESET_COLOR "%d\n", philo->b_mutex);
// 	printf(CYAN "lst_meal: " RESET_COLOR "%ld\n", philo->lst_meal);
// 	printf("\n");
// }
