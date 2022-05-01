/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 04:17:42 by maboulho          #+#    #+#             */
/*   Updated: 2022/03/23 21:39:51 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long int	i;

	i = n;
	if (i < 0)
	{
		write (1, "-", 1);
		i = -i;
	}
	if (i >= 10)
	{
		ft_putnbr(i / 10);
		ft_putchar(i % 10 + '0');
	}
	else
		ft_putchar(i + '0');
}

void	receive(int sig)
{
	static int	i;
	static char	b;

	if (i == 0)
	i = 8;
	if (sig == SIGUSR1)
		b = (1 << (i - 1)) | b;
	else if (sig == SIGUSR2)
		b = (0 << (i - 1)) | b;
	i--;
	if (i == 0)
	{
		write(1, &b, 1);
		i = 8;
		b = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, receive);
	signal(SIGUSR2, receive);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
