/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:32:28 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 07:09:12 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_debug_print_eat_count(t_philo *philo, t_param *param)
{
	int		i;
	char	*color;
	char	*sep;

	if (param->eat_limit == -1)
		printf("%s", BOT_D);
	else
		printf("%s", BOT_E);
	if (param->eat_limit == -1)
		return ;
	i = 0;
	while (i < param->amount)
	{
		if (philo[i].eat_count == param->eat_limit)
			color = G;
		else
			color = R;
		if (i == param->amount - 1)
			sep = EC_SEP_END;
		else
			sep = EC_SEP;
		printf("%s%s%d%s%s%s%d%s/%d%s", sep, Y, philo[i].id, X, EC_ATE,
			color, philo[i].eat_count, X, param->eat_limit, EC_TIME);
		i++;
	}
}
