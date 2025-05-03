/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:56:48 by edgribei          #+#    #+#             */
/*   Updated: 2025/04/30 14:21:36 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <vector.h>
# include <color.h>

void	put_square(void *image, t_vec2 UL, t_vec2 DR, t_color color);
void	put_line(void *image, t_vec2 a, t_vec2 b, t_color color);
void	put_pixel_image(char *image, int sline, t_vec2 position, t_color color);
#endif
