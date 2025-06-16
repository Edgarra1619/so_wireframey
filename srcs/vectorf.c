/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:34:24 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 19:34:34 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_vecf3	sum_vecf3(const t_vecf3 a, const t_vecf3 b)
{
	return ((t_vecf3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vecf2	sum_vecf2(const t_vecf2 a, const t_vecf2 b)
{
	return ((t_vecf2){a.x + b.x, a.y + b.y});
}

t_vecf3	mult_vecf3i(const t_vecf3 a, const float b)
{
	return ((t_vecf3){a.x * b, a.y * b, a.z * b});
}
