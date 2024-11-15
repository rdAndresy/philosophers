// Remplacer les tableaux de philosophes par des listes chainées

#include "philo.h"

int	ft_atoi(char *str)
{
	long int	res;
	int			i;

	res = -1;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || (str[i] != '+' && (str[i] < '0' || str[i] > '9')))
		return (res);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res == -1)
			res = 0;
		res = res * 10 + str[i++] - '0';
		if (res > INT_MAX)
			return (-1);
	}
	return ((int)res);
}

int	ft_forks_init(t_philo **philos, int i)
{
	t_philo	*curr;
	t_philo	*prev;

	prev = *philos;
	prev->lf_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!prev->lf_mutex || pthread_mutex_init(prev->lf_mutex, NULL))
		return (EXIT_FAILURE);
	prev->b_mutex = 1;
	curr = prev->next;
	while (--i > 0)
	{
		curr->lf_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!curr->lf_mutex)
			return (EXIT_FAILURE);
		prev->rf_mutex = curr->lf_mutex;
		if (pthread_mutex_init(curr->lf_mutex, NULL))
			return (EXIT_FAILURE);
		curr->b_mutex = 1;
		prev = curr;
		curr = curr->next;
	}
	prev->rf_mutex = (*philos)->lf_mutex;
	return (EXIT_SUCCESS);
}

int	ft_philos_init(t_args *args, t_philo **philos)
{
	int		i;
	t_philo	*single;

	i = 0;
	while (i < args->n_philo)
	{
		single = (t_philo *)malloc(sizeof(t_philo));
		if (!single)
			return (EXIT_FAILURE);
		single->b_mutex = 0;
		single->args = args;
		single->id = i + 1;
		single->lst_meal = ft_timestamp();
		single->loop = 0;
		single->rf_state = DOWN;
		single->lf_state = DOWN;
		single->next = NULL;
		if (*philos == NULL)
			*philos = single;
		else
			ft_lstlast(*philos)->next = single;
		i++;
	}
	ft_lstlast(*philos)->next = *philos;
	return (EXIT_SUCCESS);
}

int	ft_args_init(t_args **args, int ac, char *av[])
{
	(*args) = (t_args *)malloc(sizeof(t_args));
	if (!args)
		return (ft_print_error("Malloc failed\n"), EXIT_FAILURE);
	(*args)->n_philo = ft_atoi(av[1]);
	if (ac == 6)
		(*args)->n_loop = ft_atoi(av[5]);
	else
		(*args)->n_loop = -2;
	(*args)->b_dead = 0;
	(*args)->b_mutex = 0;
	(*args)->tt_die = ft_atoi(av[2]) * 1000;
	(*args)->tt_eat = ft_atoi(av[3]) * 1000;
	(*args)->tt_sleep = ft_atoi(av[4]) * 1000;
	if ((*args)->n_philo == -1 || (*args)->n_loop == -1
		|| (*args)->tt_die / 1000 == -1 || (*args)->tt_eat / 1000 == -1
		|| (*args)->tt_sleep / 1000 == -1)
		return (ft_print_error("Invalid arguments"), EXIT_FAILURE);
	if (pthread_mutex_init(&(*args)->philo_mutex, NULL)
		|| pthread_mutex_init(&(*args)->death_mutex, NULL)
		|| pthread_mutex_init(&(*args)->print_mutex, NULL))
		return (ft_print_error("Mutex failed"), EXIT_FAILURE);
	(*args)->b_mutex = 1;
	return ((*args)->b_mutex = 0, EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_args	*args;
	t_philo	*philos;

	philos = NULL;
	args = NULL;
	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arguments\n", NULL, NULL));
	ft_timestamp();
	if (ft_args_init(&args, ac, av))
		return (ft_error("\n", args, NULL));
	if (ft_philos_init(args, &philos))
		return (ft_error("Malloc failed\n", args, philos));
	if (ft_forks_init(&philos, args->n_philo))
		return (ft_error("Mutex failed\n", args, philos));
	if (ft_philosophers(philos))
		return (ft_error("\n", args, philos));
	ft_error(NULL, args, philos);
	return (EXIT_SUCCESS);
}
