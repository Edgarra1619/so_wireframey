/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:56:48 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/05 15:19:22 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <vector.h>
# include <color.h>
# include <state.h>
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 640
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif

void	put_square(t_image *image, t_vec2 UL, t_vec2 DR, t_color color);
void	put_line(t_image *image, t_vec2 a, t_vec2 b, t_color color);
void	put_pixel_image(t_image *image, t_vec2 position, t_color color);
void	render_map(t_image *img, t_state *state);

#endif
