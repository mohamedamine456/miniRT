/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:53:58 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 20:41:14 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		color_generate(t_ray ray, t_scene scene)
{
	t_hited		hited;
	t_vector	color;
	t_object	*obj;

	obj = scene.obj;
	hited = initialize_hited();
	color = vec_initialize(0, 0, 0);
	while (scene.obj->shape != 0)
	{
		help_generate_rays(ray, scene.obj, &hited);
		if (scene.obj->next != NULL)
			scene.obj = scene.obj->next;
		else
			break ;
	}
	color = calculate_color(hited, obj, scene);
	return (color);
}

t_hited			initialize_hited(void)
{
	t_hited		hited;

	hited.yes = 0;
	hited.t = 1e6;
	hited.p = vec_initialize(0, 0, 0);
	hited.color = vec_initialize(0, 0, 0);
	hited.normal = vec_initialize(0, 0, 0);
	hited.obj = 0;
	return (hited);
}

void			help_generate_rays(t_ray ray, t_object *obj, t_hited *hited)
{
	if (obj->shape == 's')
		if (hit_sphere(ray, obj, hited))
			hited->yes = 1;
	if (obj->shape == 'p')
		if (hit_plan(obj, ray, hited))
			hited->yes = 1;
	if (obj->shape == 't')
		if (hit_triangle(obj, ray, hited))
			hited->yes = 1;
	if (obj->shape == 'c')
		if (hit_cylindre(obj, ray, hited))
			hited->yes = 1;
	if (obj->shape == 'q')
		if (hit_square(obj, ray, hited))
			hited->yes = 1;
}

void			help_generate_shadows(t_ray shad_ray, t_object *obj,
		t_hited *hit_shape, float distance)
{
	if (obj->shape == 's')
		if (hit_sphere(shad_ray, obj, hit_shape)
				&& hit_shape->t <= distance)
			hit_shape->yes = 1;
	if (obj->shape == 'p')
		if (hit_plan(obj, shad_ray, hit_shape)
				&& hit_shape->t <= distance)
			hit_shape->yes = 1;
	if (obj->shape == 't')
		if (hit_triangle(obj, shad_ray, hit_shape)
				&& hit_shape->t <= distance)
			hit_shape->yes = 1;
	if (obj->shape == 'c')
		if (hit_cylindre(obj, shad_ray, hit_shape)
				&& hit_shape->t <= distance)
			hit_shape->yes = 1;
	if (obj->shape == 'q')
		if (hit_square(obj, shad_ray, hit_shape)
				&& hit_shape->t <= distance)
			hit_shape->yes = 1;
}

void			camera_rotation_helper(t_scene scene,
		t_data_generate dg, int key)
{
	dg.r.origin = scene.cam->origin;
	dg.r.direction.x = dg.x - (scene.resol.width / 2);
	dg.r.direction.y = dg.y - (scene.resol.height / 2);
	dg.r.direction.z = scene.cam->normal.z * scene.resol.width
		/ (2 * tan((scene.cam->fov * M_PI) / 360));
	vec_normalize(&(dg.r.direction));
	dg.r.direction = apply_rotation(dg.r.direction, key, scene.cam);
	vec_normalize(&(dg.r.direction));
	dg.color = color_generate(dg.r, scene);
	dg.pos = (dg.x + (scene.resol.height - 1 - dg.y)
			* scene.resol.width) * 4;
	scene.window.img_add[dg.pos + 2] = (char)dg.color.x;
	scene.window.img_add[dg.pos + 1] = (char)dg.color.y;
	scene.window.img_add[dg.pos] = (char)dg.color.z;
}
