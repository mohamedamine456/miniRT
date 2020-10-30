/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:53:58 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 12:37:15 by mlachheb         ###   ########.fr       */
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
		if (scene.obj->shape == 's')
			if (hit_sphere(ray, scene.obj, &hited))
				hited.yes = 1;
		if (scene.obj->shape == 'p')
			if (hit_plan(scene.obj, ray, &hited))
				hited.yes = 1;
		if (scene.obj->shape == 't')
			if (hit_triangle(scene.obj, ray, &hited))
				hited.yes = 1;
		if (scene.obj->shape == 'c')
			if (hit_cylindre(scene.obj, ray, &hited))
				hited.yes = 1;
		if (scene.obj->shape == 'q')
			if (hit_square(scene.obj, ray, &hited))
				hited.yes = 1;
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
