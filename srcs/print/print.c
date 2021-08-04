/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:31:06 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/04 20:02:33 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	print_message(t_philosopher *philosopher, char *str)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (!philosopher->data->end)
		printf("\e[0;32m%-5lu\e[0m | \e[0;33m%d\e[0m %s\n", get_time_diff(philosopher->data->start_time, time) / 1000, philosopher->index, str);
}
