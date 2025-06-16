/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:53:29 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 19:53:30 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	clamp(const int num, const int min, const int max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

float	clampf(float num, float min, float max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

int	lerp(const int a, const int b, const float t)
{
	if (t >= 1)
		return (b);
	if (t <= 0)
		return (a);
	return (a * (1 - t) + b * t);
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
