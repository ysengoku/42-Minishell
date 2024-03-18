/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:06:25 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 21:50:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>

int				ft_write_char(int c, int out);
int				ft_write_string(char *s, int out);
int				ft_fprintf(int out, const char *c, ...);
int				ft_direction(const char c, va_list ptr, int out);
int				ft_putnbr(int n, int out);
int				ft_write_int(int rep, int out);
int				ft_write_un_dec(unsigned int n, int out);
int				ft_write_hexa_low(unsigned int n, int out);
int				ft_write_hexa_upp(unsigned int n, int out);
int				ft_write_ptr(unsigned long n, int out);
char			*ft_itoa_ul_16(unsigned long n);
int				ft_expnt(int a);

#endif
