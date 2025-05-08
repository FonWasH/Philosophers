/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:26:08 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:29 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_init_philo(t_param *param)
{
	t_philo	*philo;
	int		i;

	if (DEBUG)
		ft_debug_print_label();
	philo = malloc(sizeof(t_philo) * param->amount);
	if (!philo)
		ft_error(ERROR_MEM, NULL, param);
	i = 0;
	while (i < param->amount)
	{
		philo[i].pid = -1;
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].last_meal = param->start_time;
		philo[i].param = param;
		i++;
	}
	ft_start(philo, param);
}

static void	ft_init_semaphore(t_param *param)
{
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_MSG);
	sem_unlink(SEM_FORKS);
	param->sem_stop = NULL;
	param->sem_msg = NULL;
	param->sem_forks = NULL;
	param->sem_stop = sem_open(SEM_STOP, O_CREAT, 0600, 1);
	if (param->sem_stop == SEM_FAILED)
		ft_error(ERROR_SEM, NULL, NULL);
	param->sem_msg = sem_open(SEM_MSG, O_CREAT, 0600, 1);
	if (param->sem_msg == SEM_FAILED)
		ft_error(ERROR_SEM, NULL, param);
	param->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0600, param->amount);
	if (param->sem_forks == SEM_FAILED)
		ft_error(ERROR_SEM, NULL, param);
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
	ft_init_semaphore(&param);
	ft_init_philo(&param);
}
