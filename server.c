/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:02:36 by fcespede          #+#    #+#             */
/*   Updated: 2023/03/04 17:00:00 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"
#include "libft/libft.h"

static char	*g_str;

static int	ft_pow(int base, int exp)
{
	int	res;

	res = 1;
	while (exp != 0)
	{
		res *= base;
		exp--;
	}
	return (res);
}

static int	to_decimal(int n)
{
	int	decimal;
	int	i;
	int	tmp;

	decimal = 0;
	i = 0;
	while (n != 0)
	{
		tmp = n % 10;
		n /= 10;
		decimal += tmp * ft_pow(2, i);
		i++;
	}
	return (decimal);
}

static char	ft_convert(char *binary_str)
{
	int		i;
	char	*str;
	int		num;

	i = 0;
	str = ft_strdup("");
	if (!str)
	{
		free(binary_str);
		exit(0);
	}
	while (i < 8)
		str = ft_chrjoin(str, binary_str[i++]);
	num = to_decimal(ft_atoi(str));
	free(str);
	return (num);
}

static void	ft_handler(int signum, siginfo_t *info, void *context)
{
	int		len;
	int		count;
	int		i;
	char	output;

	count = 0;
	i = 0;
	(void)context;
	if (!g_str)
		g_str = ft_strdup("");
	if (!g_str)
		exit(0);
	if (signum == SIGUSR1)
		g_str = ft_chrjoin(g_str, '0');
	if (signum == SIGUSR2)
		g_str = ft_chrjoin(g_str, '1');
	len = ft_strlen(g_str);
	if (g_str && ft_strlen(g_str) % 8 == 0)
	{
		output = ft_convert(g_str);
		write(1, &output, 1);
		free(g_str);
		g_str = NULL;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	printf("Mi PID es %d\n", getpid());
	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		printf("Fallo SIGUSR1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		printf("Fallo SIGUSR2");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	exit(0);
}
