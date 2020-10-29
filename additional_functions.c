/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:17 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/28 11:39:23 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window		set_new_window(t_resolution resol, char *name)
{
	t_window window;

	window.endian = 0;
	window.bits_pixel = 0;
	window.size_line = 0;
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, resol.width,
			resol.height, name);
	window.img_ptr = mlx_new_image(window.mlx_ptr, resol.width, resol.height);
	window.img_add = mlx_get_data_addr(window.img_ptr, &(window.bits_pixel),
			&(window.size_line), &(window.endian));
	return (window);
}

t_data_generate	dg_initialize(t_camera *cam)
{
	t_data_generate dg;

	dg.r.origin = vec_initialize(cam->origin.x, cam->origin.y, cam->origin.z);
	dg.pos = 0;
	dg.x = 0;
	dg.y = 0;
	dg.r.direction = vec_initialize(0, 0, 0);
	dg.color = vec_initialize(0, 0, 0);
	return (dg);
}

t_object		*object_init(void)
{
	t_object *obj;

	obj = malloc(sizeof(t_object));
	obj->shape = 0;
	obj->id = 0;
	obj->selected = 0;
	obj->center = vec_initialize(0, 0, 0);
	obj->diameter = 0;
	obj->point = vec_initialize(0, 0, 0);
	obj->normal = vec_initialize(0, 0, 0);
	obj->heigth = 0;
	obj->first_point = vec_initialize(0, 0, 0);
	obj->second_point = vec_initialize(0, 0, 0);
	obj->third_point = vec_initialize(0, 0, 0);
	obj->color = vec_initialize(0, 0, 0);
	obj->next = NULL;
	return (obj);
}

t_object		*ft_objlast(t_object *object)
{
	if (object != NULL)
		while (object->next != NULL)
			object = object->next;
	return (object);
}

t_camera		*cam_init(void)
{
	t_camera *cam;

	cam = malloc(sizeof(t_camera));
	cam->fov = -1;
	cam->origin = vec_initialize(0, 0, 0);
	cam->normal = vec_initialize(0, 0, 0);
	cam->rotation_angle = 12;
	cam->axe = 0;
	cam->next = NULL;
	cam->previous = NULL;
	return (cam);
}
