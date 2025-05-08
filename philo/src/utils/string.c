/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:06:19 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:09:40 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_msg(t_param *param, int id, t_event event, bool need_mutex)
{
	if (need_mutex)
		pthread_mutex_lock(&param->mutex_stop);
	if (!param->stop)
	{
		if (DEBUG)
			ft_debug_print_event(param, id, event);
		else
			printf("%ld %d %s\n", ft_time() - param->start_time,
				id, ft_get_string_event(event));
	}
	if (need_mutex)
		pthread_mutex_unlock(&param->mutex_stop);
}
