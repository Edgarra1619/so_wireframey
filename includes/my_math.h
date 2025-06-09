/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:55:10 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/14 18:10:52 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MATH_H
# define MY_MATH_H

int	clamp(const int num, const int max, const int min);
float	clampf(const float num, const float max, const float min);
int	lerp(const int a, const int b, const float t);
int max(const int a, const int b);
int abs(const int a);
#endif
