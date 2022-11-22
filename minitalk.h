/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbasilio <jbasilio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:50:16 by jbasilio          #+#    #+#             */
/*   Updated: 2022/11/21 22:50:18 by jbasilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft/libft.h"

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define BLU	"\x1B[34m"
# define RST	"\x1B[0m"

typedef struct s_data {
	int				i;
	unsigned char	c;
	char			*str;
	char			*tmp;
	pid_t			cli_pid;
}				t_data;

#endif
