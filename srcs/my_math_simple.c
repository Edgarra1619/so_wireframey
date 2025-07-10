/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:50:38 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 16:50:53 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	minf(const float a, const float b)
{
	if (a > b)
		return (b);
	return (a);
}

int	max(const int a, const int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	abs(const int a)
{
	if (a < 0)
		return (-a);
	return (a);
}
