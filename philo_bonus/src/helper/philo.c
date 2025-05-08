/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:58:10 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:34 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_clear(t_philo *philo, t_param *param, bool do_kill)
{
	int	i;

	i = 0;
	while (do_kill && i < param->amount)
	{
		if (philo[i].pid != -1)
			kill(philo[i].pid, SIGKILL);
		i++;
	}
	sem_close(param->sem_stop);
	sem_close(param->sem_msg);
	sem_close(param->sem_forks);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_MSG);
	sem_unlink(SEM_FORKS);
	free(philo);
}

static void	ft_eating(t_philo *philo)
{
	sem_wait(philo->param->sem_forks);
	ft_msg(philo->param, philo->id, TAKE);
	sem_wait(philo->param->sem_forks);
	ft_msg(philo->param, philo->id, TAKE);
	ft_msg(philo->param, philo->id, EAT);
	philo->last_meal = ft_time();
	philo->eat_count++;
	ft_usleep(philo->param->time_to_eat);
	sem_post(philo->param->sem_forks);
	sem_post(philo->param->sem_forks);
}

static void	*ft_status(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->param->time_to_die + 1);
	if ((ft_time() - philo->last_meal > philo->param->time_to_die)
		&& *(int *)philo->param->sem_stop
		&& (philo->eat_count != philo->param->eat_limit))
	{
		ft_msg(philo->param, philo->id, DIE);
		sem_wait(philo->param->sem_stop);
		sem_post(philo->param->sem_forks);
		sem_post(philo->param->sem_forks);
	}
	return (NULL);
}

static void	ft_events(t_philo *philo, int i)
{
	if (philo[i].id % 2 == 0)
		ft_usleep(10);
	while (*(int *)philo->param->sem_stop
		&& (philo[i].eat_count != philo[i].param->eat_limit))
	{
		if (pthread_create(&philo[i].status, NULL, ft_status, &philo[i]) == -1)
			ft_error(ERROR_TCREATE, philo, philo[i].param);
		pthread_detach(philo[i].status);
		ft_eating(&philo[i]);
		ft_msg(philo[i].param, philo[i].id, SLEEP);
		ft_usleep(philo[i].param->time_to_sleep);
		ft_msg(philo[i].param, philo[i].id, THINK);
	}
	ft_usleep(philo[i].param->time_to_die + 1);
	ft_clear(philo, philo[i].param, false);
	exit(EXIT_SUCCESS);
}

void	ft_start(t_philo *philo, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->amount)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			ft_error(ERROR_FORK, philo, param);
		if (philo[i].pid == 0)
			ft_events(philo, i);
		i++;
	}
	i = 0;
	while (i < param->amount)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	if (DEBUG)
		printf("%s", BOT_D);
	ft_clear(philo, param, true);
}
