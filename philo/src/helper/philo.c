/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:06:35 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:09:34 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_msg(philo->param, philo->id, TAKE, true);
	pthread_mutex_lock(philo->right_fork);
	ft_msg(philo->param, philo->id, TAKE, true);
	ft_msg(philo->param, philo->id, EAT, true);
	philo->last_meal = ft_time();
	philo->eat_count++;
	ft_usleep(philo->param->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*ft_status(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->param->time_to_die + 1);
	if ((ft_time() - philo->last_meal > philo->param->time_to_die)
		&& !philo->param->stop && (philo->eat_count != philo->param->eat_limit))
	{
		pthread_mutex_lock(&philo->param->mutex_stop);
		ft_msg(philo->param, philo->id, DIE, false);
		philo->param->stop = true;
		pthread_mutex_unlock(&philo->param->mutex_stop);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

void	*ft_events(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!philo->param->stop && (philo->eat_count != philo->param->eat_limit))
	{
		if (pthread_create(&philo->status, NULL, ft_status, philo) == -1)
			ft_error(ERROR_TCREATE, philo, philo->param->forks);
		pthread_detach(philo->status);
		ft_eating(philo);
		ft_msg(philo->param, philo->id, SLEEP, true);
		ft_usleep(philo->param->time_to_sleep);
		ft_msg(philo->param, philo->id, THINK, true);
	}
	ft_usleep(philo->param->time_to_die + 1);
	return (NULL);
}

void	ft_clear(t_philo *philo, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->amount)
	{
		if (pthread_join(philo[i].events, NULL) == -1)
			ft_error(ERROR_TJOIN, philo, param->forks);
		pthread_mutex_destroy(&param->forks[i]);
		i++;
	}
	if (DEBUG)
		ft_debug_print_eat_count(philo, param);
	pthread_mutex_destroy(&param->mutex_stop);
	free(param->forks);
	free(philo);
}
