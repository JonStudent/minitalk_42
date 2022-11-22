/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbasilio <jbasilio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 03:19:33 by jbasilio          #+#    #+#             */
/*   Updated: 2022/11/21 03:19:41 by jbasilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	build_str(t_data *data)
{
	char	c_buf[2];

	c_buf[0] = data->c;
	data->tmp = data->str;
	if (data->str)
		data->str = ft_strjoin(data->str, c_buf);
	else
		data->str = ft_strdup(c_buf);
	free(data->tmp);
}

static void	decode(int sig, siginfo_t *info, void *context)
{
	static t_data	data;

	(void)context;
	if (info->si_pid)
		data.cli_pid = info->si_pid;
	data.c |= (sig == SIGUSR2);
	if (++data.i == 8)
	{
		data.i = 0;
		if (!data.c && ft_printf("Message: ["RST"%s"GRN"]\n", data.str))
		{
			free(data.str);
			data.str = 0;
			kill(data.cli_pid, SIGUSR2);
			return ;
		}
		build_str(&data);
		data.c = 0;
	}
	else
		data.c <<= 1;
	kill(data.cli_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf(RED"\n🔴 LIVE\n"RST"Server PID: "GRN"%d\n\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = decode;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
