/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:41:33 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/28 11:43:17 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera						*ft_camlast(t_camera *cam)
{
	if (cam != NULL)
		while (cam->next != NULL)
			cam = cam->next;
	return (cam);
}

t_light							*light_init(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->intensite = -1;
	light->origin = vec_initialize(0, 0, 0);
	light->color = vec_initialize(0, 0, 0);
	light->next = NULL;
	return (light);
}

t_light							*ft_lightlast(t_light *light)
{
	if (light != NULL)
		while (light->next != NULL)
			light = light->next;
	return (light);
}

t_vector						apply_rotation(t_vector direction,
		int key, t_camera *cam)
{
	t_vector	new_direction;
	float		angle;

	angle = cam->rotation_angle;
	if ((key == 7 && cam->axe == 'z'))
	{
		new_direction.x = direction.x;
		new_direction.y = direction.y * cos(angle) - direction.z * sin(angle);
		new_direction.z = direction.z * cos(angle) + direction.y * sin(angle);
	}
	if (key == 16 && cam->axe == 'z')
	{
		new_direction.x = direction.x * cos(angle) + direction.z * sin(angle);
		new_direction.y = direction.y;
		new_direction.z = direction.y * cos(angle) - direction.z * sin(angle);
	}
	if (key == 6 && cam->axe == 'z')
	{
		new_direction.x = direction.x * cos(angle) - direction.y * sin(angle);
		new_direction.y = direction.y * cos(angle) + direction.x * sin(angle);
		new_direction.z = direction.z;
	}
	if (key != 7 && key != 16 && key != 6)
		return (direction);
	return (new_direction);
}

t_calculate_color_data			initialize_color_data(t_ambiante amb)
{
	t_calculate_color_data cc_data;

	cc_data.color = vec_initialize(0, 0, 0);
	cc_data.diffuse = vec_initialize(0, 0, 0);
	cc_data.ambient = vec_multiple_n(amb.ambiante, amb.color);
	cc_data.specular = vec_initialize(0, 0, 0);
	cc_data.intensite = vec_initialize(0, 0, 0);
	cc_data.dot = 0;
	return (cc_data);
}
