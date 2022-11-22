/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbasilio <jbasilio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 03:19:50 by jbasilio          #+#    #+#             */
/*   Updated: 2022/11/21 03:20:00 by jbasilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	encode(int srv_pid, char *str)
{
	static int		i = 7;
	static char		*str_p;

	if (str)
		str_p = str;
	if (*str_p)
	{
		if (*str_p >> i & 1)
			kill(srv_pid, SIGUSR2);
		else
			kill(srv_pid, SIGUSR1);
		if (!i-- && str_p++)
			i = 7;
	}
	else
		kill(srv_pid, SIGUSR1);
}

static void	feedback(int sig, siginfo_t *info, void *context)
{
	static int			srv_pid;
	static unsigned int	feed;

	if (info->si_pid)
		srv_pid = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1 && ++feed)
		encode(srv_pid, NULL);
	else if (ft_printf(GRN"["RST"Server"GRN"]"))
		exit(!ft_printf(RST" - recived: "BLU"%d "GRN"✔✔\n", feed / 8));
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		return (1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = feedback;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	encode(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
