/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:45:52 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:09:30 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	ft_new_philo(int i, t_param *param)
{
	t_philo	philo;

	philo.id = i + 1;
	philo.eat_count = 0;
	philo.last_meal = param->start_time;
	philo.param = param;
	philo.left_fork = &param->forks[i];
	if (i + 1 == param->amount)
		philo.right_fork = &param->forks[0];
	else
		philo.right_fork = &param->forks[i + 1];
	return (philo);
}

static void	ft_init_philo(t_param *param)
{
	t_philo	*philo;
	int		i;

	if (DEBUG)
		ft_debug_print_label();
	philo = malloc(sizeof(t_philo) * param->amount);
	if (!philo)
		ft_error(ERROR_MEM, NULL, param->forks);
	i = 0;
	while (i < param->amount)
	{
		philo[i] = ft_new_philo(i, param);
		if (pthread_create(&philo[i].events, NULL, ft_events, &philo[i]) == -1)
			ft_error(ERROR_TCREATE, philo, param->forks);
		i++;
	}
	ft_clear(philo, param);
}

static pthread_mutex_t	*ft_init_forks(int amount)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * amount);
	if (!forks)
		ft_error(ERROR_MEM, NULL, NULL);
	i = 0;
	while (i < amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static bool	ft_check_args(int ac, char *av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strisdigit(av[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_init(int ac, char *av[])
{
	t_param	param;

	if (!ft_check_args(ac, av))
		ft_error(ERROR_ARG, NULL, NULL);
	param.amount = ft_atol(av[1]);
	param.time_to_die = ft_atol(av[2]);
	param.time_to_eat = ft_atol(av[3]);
	param.time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		param.eat_limit = ft_atol(av[5]);
	else
		param.eat_limit = -1;
	if ((param.amount <= 0 || param.amount > INT_MAX)
		|| (param.time_to_die <= 0 || param.time_to_die > INT_MAX)
		|| (param.time_to_eat <= 0 || param.time_to_eat > INT_MAX)
		|| (param.time_to_sleep <= 0 || param.time_to_sleep > INT_MAX)
		|| (ac == 6 && (param.eat_limit <= 0 || param.eat_limit > INT_MAX)))
		ft_error(ERROR_ARG, NULL, NULL);
	param.start_time = ft_time();
	param.stop = false;
	pthread_mutex_init(&param.mutex_stop, NULL);
	param.forks = ft_init_forks(param.amount);
	ft_init_philo(&param);
}
