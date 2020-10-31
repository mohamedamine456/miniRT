/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:43:20 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/31 13:14:04 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		translate_vec(t_object *object, t_light *light,
		int key, t_scene scene)
{
	t_object	*obj;
	t_vector	vec_trans;

	obj = object;
	vec_trans = calculate_trans_vec(key);
	if (obj->shape == 's' || obj->shape == 'q' || obj->shape ==
			'c' || obj->shape == 'p')
	{
		while (obj->shape != 0)
		{
			if (obj->shape == scene.selected)
				obj->center = vec_plus(obj->center, vec_trans);
			if (obj->shape == 't' && obj->shape == scene.selected)
			{
				obj->first_point = vec_plus(obj->first_point, vec_trans);
				obj->second_point = vec_plus(obj->second_point, vec_trans);
				obj->third_point = vec_plus(obj->third_point, vec_trans);
			}
			if (obj->next != NULL)
				obj = obj->next;
			else
				break ;
		}
	}
	translate_vec_light_cam(light, &vec_trans, scene);
}

void		translate_vec_light_cam(t_light *light,
		t_vector *vt, t_scene scene)
{
	t_light*lum;

	if (scene.selected == 'a')
		scene.cam->origin = vec_plus(scene.cam->origin, *vt);
	if (scene.selected == 'l')
	{
		lum = light;
		while (lum->intensite != -1)
		{
			lum->origin = vec_plus(lum->origin, *vt);
			if (lum->next != NULL)
				lum = lum->next;
			else
				break ;
		}
	}
}

t_vector	calculate_trans_vec(int key)
{
	t_vector trans_vec;

	trans_vec = vec_initialize(0, 0, 0);
	if (key == 124)
		trans_vec = vec_initialize(4, 0, 0);
	if (key == 123)
		trans_vec = vec_initialize(-4, 0, 0);
	if (key == 126)
		trans_vec = vec_initialize(0, 0, 4);
	if (key == 125)
		trans_vec = vec_initialize(0, 0, -4);
	if (key == 32)
		trans_vec = vec_initialize(0, 4, 0);
	if (key == 2)
		trans_vec = vec_initialize(0, -4, 0);
	return (trans_vec);
}

void		rotation_vec(int key, t_object *object, t_scene scene)
{
	t_object *obj;

	obj = object;
	while (obj->shape != 0)
	{
		if ((obj->shape == 'q' || obj->shape == 'c') &&
				scene.selected == obj->shape)
		{
			if (key == 7)
				obj->normal = vec_initialize(1, 0, 0);
			if (key == 16)
				obj->normal = vec_initialize(0, 1, 0);
			if (key == 6)
				obj->normal = vec_initialize(0, 0, 1);
		}
		if (obj->shape == 'p' && obj->shape == scene.selected)
			rotation_vec_cont(key, obj);
		if (obj->next != NULL)
			obj = obj->next;
		else
			break ;
	}
}

void		rotation_vec_cont(int key, t_object *obj)
{
	if (key == 7)
		obj->normal = vec_initialize(-1, 0, 0);
	if (key == 16)
		obj->normal = vec_initialize(0, -1, 0);
	if (key == 6)
		obj->normal = vec_initialize(0, 0, 1);
}
