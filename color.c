/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:29:53 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 19:47:54 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		calculate_color(t_hited hited, t_object *obj, t_scene scene)
{
	t_calculate_color_data	cc;
	int						shad;
	t_light					*lum;

	cc = initialize_color_data(scene.amb);
	if (hited.yes == 1)
	{
		lum = scene.light;
		while (lum->intensite != -1)
		{
			calculate_color_helper(&cc, hited, lum);
			if (lum->next != NULL)
				lum = lum->next;
			else
				break ;
		}
		cc.ambient = vec_multiple_n(scene.amb.ambiante,
				vec_plus(hited.color, scene.amb.color));
		cc.color = vec_plus(cc.ambient, vec_plus(cc.diffuse, cc.specular));
		cc.color = set_to_range(cc.color);
		shad = calculate_shadow(hited, obj, scene.light);
		if (shad == 1)
			cc.color = vec_multiple_n(scene.amb.ambiante, hited.color);
	}
	return (cc.color);
}

int				calculate_shadow(t_hited hited, t_object *obj, t_light *light)
{
	t_ray		shad_ray;
	t_hited		hit_shape;

	shad_ray.origin = vec_plus(hited.p, vec_initialize(0.01, 0.01, 0.01));
	while (light->intensite != -1)
	{
		shad_ray.direction = vec_minus(light->origin, hited.p);
		vec_normalize(&(shad_ray.direction));
		hit_shape = calculate_shadow_helper(hited, obj, light, shad_ray);
		if (hit_shape.yes == 1 && hit_shape.obj != hited.obj &&
				light->intensite > 0)
			return (1);
		if (light->next != NULL)
			light = light->next;
		else
			break ;
	}
	return (0);
}

t_hited			calculate_shadow_helper(t_hited hited,
		t_object *object, t_light *light, t_ray shad_ray)
{
	float		distance;
	t_hited		hit_shape;
	t_object	*obj;

	hit_shape.t = 1e6;
	hit_shape.yes = 0;
	distance = vec_lenght(vec_minus(light->origin, hited.p));
	obj = object;
	while (obj->shape != 0)
	{
		help_generate_shadows(shad_ray, obj, &hit_shape, distance);
		if (obj->next != NULL)
			obj = obj->next;
		else
			break ;
	}
	return (hit_shape);
}

void			calculate_color_helper(t_calculate_color_data *cc,
		t_hited hited, t_light *lum)
{
	cc->intensite = vec_multiple_n(lum->intensite, lum->color);
	cc->ll = vec_minus(lum->origin, hited.p);
	vec_normalize(&(cc->ll));
	cc->dot = vec_dot(cc->ll, hited.normal);
	cc->dot = cc->dot > 0 ? cc->dot : 0;
	cc->diffuse = vec_plus(cc->diffuse, vec_multiple_n(cc->dot, cc->intensite));
	cc->ll = vec_multiple_n(-1, cc->ll);
	cc->reflect = vec_minus(vec_multiple_n(2 * vec_dot(hited.normal,
					cc->ll), hited.normal), cc->ll);
	cc->dot = vec_dot(cc->reflect, cc->ll);
	cc->dot = cc->dot > 0 ? cc->dot : 0;
	cc->specular = vec_plus(cc->specular, vec_multiple_n(pow(cc->dot,
					10), cc->intensite));
}

t_vector		set_to_range(t_vector col)
{
	if (col.x > 255)
		col.x = 255;
	if (col.x < 0)
		col.x = 0;
	if (col.y > 255)
		col.y = 255;
	if (col.y < 0)
		col.y = 0;
	if (col.z > 255)
		col.z = 255;
	if (col.z < 0)
		col.z = 0;
	return (col);
}
