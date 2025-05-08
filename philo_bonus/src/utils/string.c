/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:56:08 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:42 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_get_string_event(t_event event)
{
	static const char	*str[5] = {
		TAKEN_FORK,
		IS_EATING,
		IS_SLEEPING,
		IS_THINKING,
		DIED
	};

	return ((char *)str[event]);
}

char	*ft_get_emoji_event(t_event event)
{
	static const char	*str[5] = {
		EMOJI_FORK,
		EMOJI_EAT,
		EMOJI_SLEEP,
		EMOJI_THINK,
		EMOJI_DEAD
	};

	return ((char *)str[event]);
}

void	ft_msg(t_param *param, int id, t_event event)
{
	sem_wait(param->sem_msg);
	if (*(int *)param->sem_stop)
	{
		if (DEBUG)
			ft_debug_print_event(param, id, event);
		else
			printf("%ld %d %s\n", ft_time() - param->start_time,
				id, ft_get_string_event(event));
	}
	sem_post(param->sem_msg);
}
