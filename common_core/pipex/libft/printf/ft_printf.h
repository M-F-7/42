/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:26:05 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/30 19:06:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);

int		ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
int		ft_putnbr_base(unsigned long n, char *base);
int		ft_putptr(void *ptr);
int		ft_putnbr_us(unsigned int n);

size_t	ft_strlen(const char *s);
#endif