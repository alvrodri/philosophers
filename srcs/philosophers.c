/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:04:42 by alvrodri          #+#    #+#             */
/*   Updated: 2021/07/28 11:28:13 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_error(int printf)
{
	(void)printf;
	exit(1);
	return (1);
}

unsigned long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

unsigned long	get_time_diff(struct timeval first, struct timeval second)
{
	unsigned long start;
	unsigned long end;

	start = (first.tv_sec * 1000) + (first.tv_usec / 1000);
	end = (second.tv_sec * 1000) + (second.tv_usec / 1000);
	return (ft_abs(start - end));
}

unsigned long	get_time(struct timeval *time)
{
	struct timeval tmp;

	if (time == NULL)
	{
		gettimeofday(&tmp, NULL);
		return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
	}
	else
		return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

unsigned long	ft_atoul(char *str)
{
	int	i;
	unsigned long	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if ((num * 10 + (str[i] - 48)) > 0xffffffff
			|| !(str[i] >= '0' && str[i] <= '9'))
			return (ft_error(printf("ft_atoul didn't work.\n")));
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

void	set_data(char **argv, int argc, t_data *data)
{
	struct timeval time;

	data->n = ft_atoul(argv[0]);
	data->time_to_die = ft_atoul(argv[1]);
	data->time_to_eat = ft_atoul(argv[2]);
	data->time_to_sleep = ft_atoul(argv[3]);
	if (argc == 5)
		data->must_eat = ft_atoul(argv[4]);
	else
		data->must_eat = 0;
	gettimeofday(&time, NULL);
	data->start_time = time;
}

void	print_message(char *msg, t_philosopher *philosopher)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%lu %d %s\n", get_time_diff(philosopher->data->start_time, time), philosopher->index, msg);
}

t_fork	*get_fork(t_philosopher *philosopher, int dir)
{
	if (dir == 0)
		return (philosopher->data->forks[philosopher->index - 1]);
	else if (dir == 1)
	{
		if (philosopher->index == philosopher->data->n)
			return (philosopher->data->forks[0]);
		else
			return (philosopher->data->forks[philosopher->index]);
	}
	return (NULL);
}

void	grab_fork(t_philosopher *philosopher, int dir)
{
	t_fork	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL || fork->in_use)
		return ;
	pthread_mutex_lock(&fork->mutex);
	fork->in_use = 1;
	philosopher->forks++;
	print_message("has taken a fork", philosopher);
}

void	release_fork(t_philosopher *philosopher, int dir)
{
	t_fork	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL)
		return ;
	fork->in_use = 0;
	philosopher->forks = 0;
	pthread_mutex_unlock(&fork->mutex);
}

void	start_philosopher(void *args)
{
	struct timeval	time;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	while (philosopher->alive)
	{
		if (philosopher->state == THINKING)
		{
			grab_fork(philosopher, 0);
			grab_fork(philosopher, 1);
			if (philosopher->forks == 2)
				philosopher->state = EATING;
		}
		else if (philosopher->state == EATING)
		{
			gettimeofday(&time, NULL);
			philosopher->last_eat = time;
			print_message("is eating", philosopher);
			usleep(philosopher->data->time_to_eat * 1000);
			philosopher->forks -= 2;
			release_fork(philosopher, 0);
			release_fork(philosopher, 1);
			philosopher->state = SLEEPING;
		}
		else if (philosopher->state == SLEEPING)
		{
			print_message("is sleeping", philosopher);
			usleep(philosopher->data->time_to_sleep * 1000);
			philosopher->state = THINKING;
			print_message("is thinking", philosopher);
		}
		if (get_time(NULL) - get_time(&philosopher->last_eat) > philosopher->data->time_to_die)
		{
			philosopher->alive = 0;
			print_message("died", philosopher);
			exit(0);
		}
	}
}

void	start_philosophers(t_data *data)
{
	struct timeval	time;
	int	i;

	i = 0;
	data->philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *) * data->n);
	data->forks = (t_fork **)malloc(sizeof(t_fork *) * data->n);
	if (!data->philosophers || !data->forks)
		exit(ft_error(printf("Could not allocate enough memory.\n")));
	while (i < data->n)
	{
		data->forks[i] = (t_fork *)malloc(sizeof(t_fork));
		data->forks[i]->in_use = 0;
		i++;
	}
	i = 0;
	while (i < data->n)
	{
		data->philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (!data->philosophers[i])
			exit(ft_error(printf("Could not allocate enough memory.\n")));
		pthread_mutex_init(&(data->forks[i]->mutex), NULL);
		data->philosophers[i]->index = i + 1;
		data->philosophers[i]->state = THINKING;
		data->philosophers[i]->data = data;
		data->philosophers[i]->eaten = 0;
		data->philosophers[i]->alive = 1;
		data->philosophers[i]->forks = 0;
		gettimeofday(&time, NULL);
		data->philosophers[i]->last_eat = time;
		pthread_create(&data->philosophers[i]->pid, NULL, (void *)start_philosopher, data->philosophers[i]);
		if ((i + 1) % 2 == 0)
			usleep(1000);
		i++;
	}
	pthread_create(&data->death_pid, NULL, (void *)check_death, data);
	i = 0;
	while (i < data->n)
	{
		pthread_join(data->philosophers[i]->pid, NULL);
		i++;
	}
	pthread_join(data->death_pid, NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data	data;

	if (argc > 6 || argc < 5)
		return (ft_error(printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_eat]\n", argv[0])));
	set_data(++argv, --argc, &data);
	start_philosophers(&data);
	return (0);
}
