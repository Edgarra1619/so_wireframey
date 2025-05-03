/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:52 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/03 18:20:52 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct	s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

t_vec3	sum_vec3(t_vec3 a, t_vec3 b);
t_vec3	mult_vec3i(t_vec3 a, int b);
t_vec2	sum_vec2(t_vec2 a, t_vec2 b);
#endif
