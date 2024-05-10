/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:23:37 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 16:56:49 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_var(int fd, va_list ap, const char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_putchar_fd(va_arg(ap, int), fd);
	else if (format == 's')
		i += ft_putstr_fd(va_arg(ap, char *), fd);
	else if (format == 'p')
		i += ft_putaddr_fd(va_arg(ap, void *), fd);
	else if (format == 'd' || format == 'i')
		i += ft_putnbr_fd(va_arg(ap, int), fd);
	else if (format == 'u')
		i += ft_putunbr_fd(va_arg(ap, unsigned int), fd);
	else if (format == 'x')
		i += ft_puthex_fd(va_arg(ap, unsigned int), "0123456789abcdef", fd);
	else if (format == 'X')
		i += ft_puthex_fd(va_arg(ap, unsigned int), "0123456789ABCDEF", fd);
	else if (format == '%')
		i += ft_putchar_fd('%', fd);
	else
		i += ft_putstr_fd("%(INVALID_FLAG)", fd);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	ap;

	if (!format)
		return (-1);
	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i += print_var(1, ap, *format);
		}
		else
			i += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(ap);
	return (i);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		i;
	va_list	ap;

	if (!format)
		return (-1);
	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i += print_var(fd, ap, *format);
		}
		else
			i += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(ap);
	return (i);
}
