/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 04:17:51 by maboulho          #+#    #+#             */
/*   Updated: 2022/03/24 12:36:04 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int	is_space(char a)
{
	if ((a == '\t') || (a == '\n') || (a == '\v')
		|| (a == '\f') || (a == '\r') || (a == ' '))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	i;
	int	r;

	r = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r);
}

void	send_char(char *str, int pid)
{
	int	i;
	int	a;
	int	j;
	int	res;

	i = 0;
	while (str[i])
	{
		a = str[i];
		j = 0;
		while (j < 8)
		{
			res = a & (1 << (7 - j));
			if (res != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	pid = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
	if (pid <= 0)
		write(1, " Invalid pid", 14);
	send_char(av[2], pid);
	}
	else
		write(1, "Invalid number of arguments", 29);
}
