/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:26:20 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 08:30:40 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	signal_handler(int signum);
void	signal_handler_herdoc(int signum);
void	signal_handler_input(int signum);
void	setup_signals(void);
void	set_signal_handler(t_cmd *tree);

#endif /* SIGNALS_H */