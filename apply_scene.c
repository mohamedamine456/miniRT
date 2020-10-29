/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:43:28 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/28 12:47:38 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		apply_scene(t_scene scene, t_data_generate dg, char *img_add)
{
	while (dg.x < scene.resol.width)
	{
		dg.y = 0;
		while (dg.y < scene.resol.height)
		{
			dg.r.direction = generate_direction(scene, dg.x, dg.y);
			dg.color = color_generate(dg.r, scene);
			dg.pos = (dg.x + (scene.resol.height - 1 - dg.y) *
					scene.resol.width) * 4;
			img_add[dg.pos + 2] = (char)dg.color.x;
			img_add[dg.pos + 1] = (char)dg.color.y;
			img_add[dg.pos] = (char)dg.color.z;
			dg.y++;
		}
		dg.x++;
	}
}

t_vector	generate_direction(t_scene scene, int x, int y)
{
	t_vector	direction;

	if ((scene.cam->normal.x == 1 || scene.cam->normal.x == -1) &&
			scene.cam->normal.y == 0 && scene.cam->normal.z == 0)
	{
		direction.x = scene.cam->normal.x *
			scene.resol.width / (2 * tan((scene.cam->fov / 2 * M_PI) / 180));
		direction.y = y - (scene.resol.height / 2);
		direction.z = x - (scene.resol.width / 2);
		vec_normalize(&(direction));
	}
	else if (scene.cam->normal.x == 0 && (scene.cam->normal.y == 1 ||
				scene.cam->normal.y == -1) && scene.cam->normal.z == 0)
	{
		direction.x = x - (scene.resol.width / 2);
		direction.y = scene.cam->normal.y *
			scene.resol.width / (2 * tan((scene.cam->fov / 2 * M_PI) / 180));
		direction.z = y - (scene.resol.height / 2);
		vec_normalize(&(direction));
	}
	else if (generate_direction_finish(scene, &direction, x, y))
		vec_normalize(&(direction));
	else
		ft_perror("the camera normal must be one axe with a value of 1 or -1");
	return (direction);
}

int			generate_direction_finish(t_scene scene, t_vector *direction,
		int x, int y)
{
	if (scene.cam->normal.x == 0 && scene.cam->normal.y == 0 &&
			(scene.cam->normal.z == 1 || scene.cam->normal.z == -1))
	{
		direction->x = x - (scene.resol.width / 2);
		direction->y = y - (scene.resol.height / 2);
		direction->z = scene.cam->normal.z *
			scene.resol.width / (2 * tan((scene.cam->fov / 2 * M_PI) / 180));
		return (1);
	}
	return (0);
}
