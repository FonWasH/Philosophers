/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:42:28 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:50 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static bool	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_strisdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

ssize_t	ft_atol(char *s)
{
	size_t	n;
	int		sgn;

	while (ft_isspace(*s))
		s++;
	sgn = 1 - (2 * (*s == '-'));
	s += (*s == '-' || *s == '+');
	n = 0;
	while (ft_isdigit(*s))
	{
		n = (n * 10) + (*s - '0');
		if (n > (size_t)LONG_MAX + (sgn < 0))
			return (0 - (1 * (sgn > 0)));
		s++;
	}
	return ((ssize_t)n * sgn);
}
