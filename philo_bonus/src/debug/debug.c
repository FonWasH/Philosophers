/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:58:33 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:10:19 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_debug_print_label(void)
{
	printf("%s", TOP_D);
	printf("%s %s %s  %s  %s        %s        %s\n",
		SEP, TIME, SEP, ID, SEP, EVENT, SEP);
	printf("%s", MID_D);
}

void	ft_debug_print_event(t_param *param, int id, t_event event)
{
	printf("%s % 9ld %s %s% 4d%s %s %-16s %s %s\n",
		SEP, ft_time() - param->start_time,
		SEP, Y, id, X,
		SEP, ft_get_string_event(event),
		ft_get_emoji_event(event), SEP);
}
