/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:50:34 by fcespede          #+#    #+#             */
/*   Updated: 2023/03/04 12:54:34 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"
#include "libft/libft.h"

static int	g_signal_received = 0;

static void	ft_signal(int sig)
{
	if (sig == SIGUSR1)
		g_signal_received = 1;
}

static int	to_binary(int n)
{
	int	binary;
	int	i;
	int	tmp;

	binary = 0;
	i = 1;
	while (n != 0)
	{
		tmp = n % 2;
		n /= 2;
		binary += tmp * i;
		i *= 10;
	}
	return (binary);
}

static void	ft_datasend(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		usleep(50);
		g_signal_received = 0;
		if (str[i] == '0')
			kill((pid_t)pid, SIGUSR1);
		else
			kill((pid_t)pid, SIGUSR2);
		while (!g_signal_received)
			;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	signal(SIGUSR1, ft_signal);
	if (argc == 3)
	{
		while (argv[2][i])
		{
			tmp = ft_simple_itoa_x16(to_binary((unsigned char)argv[2][i++]));
			if (!tmp)
				return (EXIT_FAILURE);
			ft_datasend(ft_atoi(argv[1]), tmp);
			free(tmp);
		}
		ft_datasend(ft_atoi(argv[1]), "0000000000000000");
	}
	else
		printf("ingresaste los parametros incorrectos");
	exit(0);
}
