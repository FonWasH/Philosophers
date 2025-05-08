/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:10:48 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:15:12 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_puterror(char *error)
{
	int ret;

	ret = write(2, NAME, ft_strlen(NAME));
	ret = write(2, error, ft_strlen(error));
	(void)ret;
}

void	ft_close_semaphores(t_param *param)
{
	if (param && param->sem_stop && param->sem_stop != SEM_FAILED)
	{
		sem_close(param->sem_stop);
		sem_unlink(SEM_STOP);
	}
	if (param && param->sem_msg && param->sem_msg != SEM_FAILED)
	{
		sem_close(param->sem_msg);
		sem_unlink(SEM_MSG);
	}
	if (param && param->sem_forks && param->sem_forks != SEM_FAILED)
	{
		sem_close(param->sem_forks);
		sem_unlink(SEM_FORKS);
	}
}

void	ft_error(char *error, t_philo *philo, t_param *param)
{
	int	i;

	i = 0;
	while (philo && i < param->amount)
	{
		if (philo[i].pid != -1)
			kill(philo[i].pid, SIGKILL);
		i++;
	}
	if (philo)
		free(philo);
	ft_puterror(error);
	exit(EXIT_FAILURE);
}
