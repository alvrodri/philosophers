/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:42:44 by alvrodri          #+#    #+#             */
/*   Updated: 2021/09/04 16:09:05 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	ft_error(int printf)
{
	(void)printf;
	return (1);
}

unsigned long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long	ft_atoul(char *str)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if ((num * 10 + (str[i] - 48)) > 0xffffffff
			|| !(str[i] >= '0' && str[i] <= '9'))
		{
			ft_error(printf("ft_atoul didn't work.\n"));
			return (-2);
		}
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}
