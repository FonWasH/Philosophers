/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:12:36 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:09:22 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_puterror(char *error)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, error, ft_strlen(error));
}

void	ft_error(char *error, t_philo *philo, pthread_mutex_t *forks)
{
	if (philo)
		free(philo);
	if (forks)
		free(forks);
	ft_puterror(error);
	exit(EXIT_FAILURE);
}
