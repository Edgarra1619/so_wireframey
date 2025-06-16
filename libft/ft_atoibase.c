/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:10 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 14:50:49 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned int	ft_atoihex(const char *str)
{
	static const char *const	base = "0123456789abcdef";
	int							num;
	const char					*dgt;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	num = 0;
	dgt = ft_strchr(base, ft_tolower(*str));
	while (dgt)
	{
		num = num * 16 + dgt - base;
		str++;
		dgt = ft_strchr(base, ft_tolower(*str));
	}
	return (num);
}
