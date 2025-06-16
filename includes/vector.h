/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:52 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 19:57:39 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vecf2
{
	float	x;
	float	y;
}	t_vecf2;

typedef struct s_vecf3
{
	float	x;
	float	y;
	float	z;
}	t_vecf3;

t_vecf3	sum_vecf3(const t_vecf3 a, const t_vecf3 b);
t_vecf3	mult_vecf3i(const t_vecf3 a, const float b);
t_vecf2	sum_vecf2(const t_vecf2 a, const t_vecf2 b);

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

t_vec3	sum_vec3(const t_vec3 a, const t_vec3 b);
t_vec3	mult_vec3i(const t_vec3 a, const int b);
t_vec2	sum_vec2(const t_vec2 a, const t_vec2 b);
#endif
