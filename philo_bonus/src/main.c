/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 09:48:17 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:55 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		ft_error(ERROR_ARG_NB, NULL, NULL);
	else
		ft_init(ac, av);
	return (0);
}
