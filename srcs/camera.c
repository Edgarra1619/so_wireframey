/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:40:32 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 16:41:32 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <state.h>
#include <math.h>
#include <my_math.h>

void	update_camera_rot(t_camera *const camera)
{
	camera->sin_rotx = sin((float) camera->rot.x / 180.0 * M_PI);
	camera->cos_rotx = cos((float) camera->rot.x / 180.0 * M_PI);
	camera->sin_roty = sin((float) camera->rot.y / 180.0 * M_PI);
	camera->cos_roty = cos((float) camera->rot.y / 180.0 * M_PI);
}

void	rotate_camera(t_camera *const camera, t_vecf2 rotation)
{
	camera->rot.y = clampf(camera->rot.y - rotation.y, 0, 90);
	camera->rot.x = camera->rot.x + rotation.x;
	if (camera->rot.x < 0)
		camera->rot.x += 360;
	if (camera->rot.x > 360)
		camera->rot.x -= 360;
	update_camera_rot(camera);
}
